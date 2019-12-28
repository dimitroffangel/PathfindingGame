#include "EnitityComponent.h"

#include <queue>

bool operator==(const Position& a, const Position& b)
{
	return a.x == b.x && a.y == b.y && a.direction == b.direction;
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

bool DoesMapHasRouteFromStartToFinish_And_WithValidSymbols(const std::vector<std::string>& map)
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
			if (map[row][col] != OBSTACLE_SYMBOL && map[row][col] != FREE_POSITION_SYMBOL)
			{
				return false;
			}

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
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y - 1][currentPosition.x])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.y--;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		if (currentPosition.x + 1 < map[0].size() && map[currentPosition.y][currentPosition.x + 1] != OBSTACLE_SYMBOL
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y][currentPosition.x + 1])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.x++;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		if (currentPosition.y + 1 < map.size() && map[currentPosition.y + 1][currentPosition.x] != OBSTACLE_SYMBOL
			&& distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1 <= distanceForEveryReachablePosition[currentPosition.y + 1][currentPosition.x])
		{
			Position newPositionToReach = currentPosition;
			newPositionToReach.y++;

			distanceForEveryReachablePosition[newPositionToReach.y][newPositionToReach.x] = distanceForEveryReachablePosition[currentPosition.y][currentPosition.x] + 1;
			positionToReach.push(newPositionToReach);
		}

		if (currentPosition.x - 1 >= 0 && map[currentPosition.y][currentPosition.x - 1] != OBSTACLE_SYMBOL
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
