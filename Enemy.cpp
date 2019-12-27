#include "Enemy.h"

void Enemy::Move()
{
	std::vector<std::string>& map = *m_Map;

	m_Map[m_Position.x][m_Position.y] = '.';

	if (m_Position.y - 1 >= 0 && map[m_Position.x][m_Position.y - 1] != OBSTACLE_SYMBOL)
	{
		m_Position.y--;
	}

	else if (m_Position.x + 1 < map[0].size() && map[m_Position.x + 1][m_Position.y] != OBSTACLE_SYMBOL)
	{
		m_Position.x++;
	}

	else if (m_Position.y + 1 < map.size() && map[m_Position.x][m_Position.y + 1] != OBSTACLE_SYMBOL)
	{
		m_Position.y++;
	}

	else if (m_Position.x - 1 >= 0 && map[m_Position.x - 1][m_Position.y] != OBSTACLE_SYMBOL)
	{
		m_Position.x--;
	}

	map[m_Position.x][m_Position.y] = 'E';
}
