#include "Enemy.h"

#include <time.h>

void Enemy::Move()
{
	std::vector<std::string>& map = *m_Map;

	map[m_Position.x][m_Position.y] = FREE_POSITION_SYMBOL;

	if (m_Position.y - 1 >= 0 && map[m_Position.y - 1][m_Position.x] != OBSTACLE_SYMBOL)
	{
		m_Position.y--;
	}

	else if (m_Position.x + 1 < map.size() && map[m_Position.y][m_Position.x + 1] != OBSTACLE_SYMBOL)
	{
		m_Position.x++;
	}

	else if (m_Position.y + 1 < map[0].size() && map[m_Position.y + 1][m_Position.x] != OBSTACLE_SYMBOL)
	{
		m_Position.y++;
	}

	else if (m_Position.x - 1 >= 0 && map[m_Position.y][m_Position.x - 1] != OBSTACLE_SYMBOL)
	{
		m_Position.x--;
	}

	map[m_Position.x][m_Position.y] = ENEMY_SYMBOL;
}

std::vector<Enemy> GenerateEnemies(std::vector<std::string>& map, const size_t numberOfElements)
{
	std::vector<Enemy> result;

	if (numberOfElements == 0)
	{
		return result;
	}

	result.reserve(numberOfElements);

	std::mt19937 generator(time(NULL));
	std::uniform_int_distribution<int> randomX_Value(0, map[0].size() - 1);
	std::uniform_int_distribution<int> randomY_Value(0, map.size() - 1);

	Position position;
	int currentEnemyX = randomX_Value(generator);
	int currentEnemyY = randomY_Value(generator);


	for (size_t i = 0; i < numberOfElements; i++)
	{	
		position.x = currentEnemyX;
		position.y = currentEnemyY;

		while (!IsEntityCollidingWithObstacle(map, position))
		{
			currentEnemyX = randomX_Value(generator);
			currentEnemyY = randomY_Value(generator);

			position.x = currentEnemyX;
			position.y = currentEnemyY;
		}

		result.push_back(Enemy(position, &map));
	}

	return result;
}

void MoveEnemies(std::vector<Enemy>& enemies)
{
	for (auto& enemy : enemies)
	{
		enemy.Move();
	}
}

bool IsPlayerCollidingWithEnemies(const Position& playerPosition, const std::vector<Enemy>& enemies)
{
	if (enemies.size() == 0)
		return false;

	for (const auto& enemy : enemies)
	{
		const Position& enemyPosition = enemy.GetPosition();

		if (playerPosition.x == enemyPosition.x && playerPosition.y == enemyPosition.y)
		{
			std::cout << "Player has collided with an enemy..." << '\n';
			return true;
		}
	}

	return false;
}
