#include "Mage.h"

void Mage::TryMoving()
{
	if (MovePosition(m_Position, m_Direction))
	{
		m_IteratedPosition.push_back(m_Position);

		if (IsPositionReusable(m_Map, m_Position))
		{
			m_AvailableRoutes.push(m_Position);
		}
		
		return;
	}

	if (m_AvailableRoutes.size() == 0)
	{
		std::cout << "TryMoving():: Player cannot move anymore, due to no more availableRoutes..." << '\n';
		return;
	}

	m_Position = m_AvailableRoutes.top();
	m_AvailableRoutes.pop();
	TryMoving();
}

bool IsPositionReusable(const std::vector<std::string>* pointerToMap, const Position& position)
{
	if (pointerToMap == nullptr)
	{
		std::cerr << "IsPositionReusable():: pointerToMap is nullptr..." << '\n';
		return false;
	}

	const std::vector<std::string>& map = *pointerToMap;

	int counterOfRoadsFromPosition = 0;

	if (position.y - 1 >= 0 && map[position.y - 1][position.x] != OBSTACLE_SYMBOL)
	{
		counterOfRoadsFromPosition++;
	}

	if (position.x + 1 < map[0].size())
	{
		if (map[position.y][position.x + 1] != OBSTACLE_SYMBOL)
			counterOfRoadsFromPosition++;
	}

	if (position.y + 1 < map.size() && map[position.y + 1][position.x] != OBSTACLE_SYMBOL)
	{
		counterOfRoadsFromPosition++;
	}

	if (position.x - 1 >= 0 && map[position.x - 1][position.y] != OBSTACLE_SYMBOL)
	{
		counterOfRoadsFromPosition++;
	}

	if (counterOfRoadsFromPosition > 1)
		return true;

	return false;
}
