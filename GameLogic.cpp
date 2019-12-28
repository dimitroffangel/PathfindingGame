#include "GameLogic.h"

#include "Enemy.h"
#include "InputComponent.h"

void GameLogic::Loop(std::vector<MapData>& data)
{
	const size_t dataSize = data.size();

	for (int i = 0; i < dataSize; i++)
	{
		std::vector<std::string>& map = data[i].map;

		PrintMap(map);

		auto enemies = GenerateEnemies(map, data[i].numberOfMonsters);

		m_PlayerClass->SetMap(map);

		{
			std::vector<Position> addedObstacles = ReadNumberOfObstacledToBeAdded(map);

			if (!DoesMapHasRouteFromStartToFinish(map))
			{
				i--;

				for (const auto& addedObstaclePostion : addedObstacles)
				{
					map[addedObstaclePostion.y][addedObstaclePostion.x] = FREE_POSITION_SYMBOL;
				}

				continue;
			}
		}

		bool isPlayerCollidingWithEnemies = false;

		while (m_PlayerClass->CanMove() || isPlayerCollidingWithEnemies)
		{
			MoveEnemies(enemies);
			m_PlayerClass->Move();
			isPlayerCollidingWithEnemies = isPlayerCollidingWithEnemies;
		}

		const Position& playerPostion = m_PlayerClass->GetPosition();

		if (playerPostion.x != map[0].size() - 1 || playerPostion.y != map.size() - 1 || isPlayerCollidingWithEnemies)
		{
			std::cout << "Game Over..." << '\n';
			return;
		}
	}

	std::cout << "You won..." << '\n';
	
}