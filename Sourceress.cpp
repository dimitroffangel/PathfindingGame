#include "Sourceress.h"

#include <vector>
#include <queue>

std::vector<std::vector<int> > Sourceress::CalculateTheDistanceToEveryPosition() const
{
	
	const std::vector<std::string>& map = *m_Map;

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

	std::queue<Position> positionToReach;
	distanceForEveryReachablePosition[m_Position.x][m_Position.y] = 0;
	positionToReach.push(m_Position);

	while (positionToReach.size() != 0)
	{
		const Position& currentPosition = positionToReach.front();

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

	for (size_t i = 0; i < mapNumberOfRows; i++)
	{
		for (size_t j = 0; j < mapNumberOfCols; j++)
		{
			if(distanceForEveryReachablePosition[i][j] < 0 || distanceForEveryReachablePosition[i][j] > 9)
				std::cout << distanceForEveryReachablePosition[i][j] << ", ";
			
			else if(distanceForEveryReachablePosition[i][j] < 10)
			{
				std::cout << " " << distanceForEveryReachablePosition[i][j] << ", ";
			}
		}

		std::cout << '\n';
	}

	return distanceForEveryReachablePosition;
}
