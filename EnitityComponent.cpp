#include "EnitityComponent.h"

#include <queue>

bool operator==(const Position& a, const Position& b)
{
	return a.x == b.x && a.y == b.y;
}

Direction GetReversedDirection(Direction direction)
{
	if (direction == directionUp)
	{
		return directionDown;
	}

	if (direction == directionDown)
	{
		return directionUp;
	}

	if (direction == directionLeft)
	{
		return directionRight;
	}

	if (direction == directionRight)
	{
		return directionLeft;
	}

	return direction;
}

bool MovePosition(Position& position, Direction direction)
{
	if (direction == directionNone)
	{
		std::cout << "MovePosition():: direction was none..." << '\n';
		return false;
	}

	if (direction == directionUp)
	{
		position.y -= 1;
		return true;
	}

	else if (direction == directionRight)
	{
		position.x += 1;
		return true;
	}

	else if (direction == directionDown)
	{
		position.y += 1;
		return true;
	}

	else if (direction == directionLeft)
	{
		position.x -= 1;
		return true;
	}
}

int GenerateNumber(std::mt19937& generator, const int fromSize, const int toSize)
{
	std::uniform_int_distribution<int> randomIntegerGenerator(fromSize, toSize);

	return randomIntegerGenerator(generator);
}

bool IsEntityCollidingWithObstacle(const std::vector<std::string>& map, const Position& position)
{
	return map[position.x][position.y] == FREE_POSITION_SYMBOL;
}

int GetNumberOfPassableObjectsOnMap(const std::vector<std::string>& map)
{
	int numberOfPassableObjectsOnMao = 0;

	for (const auto& row : map)
	{
		for (const auto& symbolOnCol : row)
		{
			if (symbolOnCol == FREE_POSITION_SYMBOL)
			{
				numberOfPassableObjectsOnMao++;
			}
		}
	}

	return numberOfPassableObjectsOnMao;
}

void PrintMap(const std::vector<std::string>& map)
{
	for (const auto& row : map)
	{
		for (const auto& col : row)
		{
			std::cout << col << " ";
		}

		std::cout << '\n';
	}
}

void AddObstacleToMap(std::vector<std::string>& map, int x, int y)
{
	if (x < 0 || x >= map.size())
	{
		std::cerr << "AddObstacleToMap():: x was invalid..." << '\n';
		return;
	}

	if (y < 0 || y >= map.size())
	{
		std::cerr << "AddObstacleToMap():: y was invalid..." << '\n';
		return;
	}

	map[x][y] = OBSTACLE_SYMBOL;
}

bool IsMapWithValidSymbols(const std::vector<std::string>& map)
{
	const size_t mapNumberOfRows = map.size();
	const size_t mapNumberOfCols = map[0].size();

	for (size_t row = 0; row < mapNumberOfRows; row++)
	{
		for (size_t col = 0; col < mapNumberOfCols; col++)
		{
			if (map[row][col] != OBSTACLE_SYMBOL && map[row][col] != FREE_POSITION_SYMBOL)
			{
				return false;
			}
		}
	}

	return true;
}

bool DoesMapHasRouteFromStartToFinish(const std::vector<std::string>& map)
{
	const size_t mapNumberOfRows = map.size();
	const size_t mapNumberOfCols = map[0].size();

	std::vector<std::vector<int> > distanceForEveryReachablePosition(mapNumberOfRows);
	
	for (size_t i = 0; i < mapNumberOfRows; i++)
	{
		distanceForEveryReachablePosition[i].reserve(mapNumberOfCols);
	}

	for (size_t row = 0; row < mapNumberOfRows; row++)
	{
		for (size_t col = 0; col < mapNumberOfCols; col++)
		{
			if (map[row][col] != OBSTACLE_SYMBOL)
				distanceForEveryReachablePosition[row].push_back(mapNumberOfCols * mapNumberOfRows);

			else
				distanceForEveryReachablePosition[row].push_back(-1);
		}
	}

	distanceForEveryReachablePosition[0][0] = 0;

	std::queue<Position> positionToReach;

	positionToReach.push(Position());

	while (positionToReach.size() != 0)
	{
		const Position& currentPosition = positionToReach.front();

		if (currentPosition.x == map[0].size() - 1 && currentPosition.y == map.size() - 1)
		{
			return true;
		}

		if (currentPosition.y - 1 >= 0 && map[currentPosition.y - 1][currentPosition.x] != OBSTACLE_SYMBOL 
			&& map[currentPosition.y - 1][currentPosition.x] != PLAYER_OBSTACLE_SYMBOL
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y - 1][currentPosition.x])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.y--;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		if (currentPosition.x + 1 < map[0].size() && map[currentPosition.y][currentPosition.x + 1] != OBSTACLE_SYMBOL 
			&& map[currentPosition.y][currentPosition.x + 1] != PLAYER_OBSTACLE_SYMBOL
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y][currentPosition.x + 1])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.x++;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		if (currentPosition.y + 1 < map.size() && map[currentPosition.y + 1][currentPosition.x] != OBSTACLE_SYMBOL
			&& map[currentPosition.y + 1][currentPosition.x] != PLAYER_OBSTACLE_SYMBOL
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y + 1][currentPosition.x])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.y++;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		if (currentPosition.x - 1 >= 0 && map[currentPosition.y][currentPosition.x - 1] != OBSTACLE_SYMBOL 
			&& map[currentPosition.y][currentPosition.x - 1] != PLAYER_OBSTACLE_SYMBOL
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y][currentPosition.x - 1])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.x--;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		positionToReach.pop();
	}

	return false;
}

void SortContainerOfMaps(std::vector<MapData>& data)
{
	auto predicate = [data](const MapData& lhs, const MapData& rhs)
	{
		const size_t lhsMapSize = lhs.map.size() * lhs.map[0].size();
		const size_t rhsMapSize = rhs.map.size() * rhs.map[0].size();

		if (lhsMapSize == rhsMapSize)
		{
			return lhs.numberOfMonsters < rhs.numberOfMonsters;
		}

		return lhsMapSize < rhsMapSize;
	};

	std::sort(data.begin(), data.end(), predicate);
}