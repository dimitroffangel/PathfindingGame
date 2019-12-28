#include "Mage.h"

#include <algorithm>

void Mage::Move()
{
	bool hasMoved = false;

	std::vector<std::string>& map = *m_Map;
	
	const bool canTeleport = m_IsTeleportingBack;
	const Direction currentDirection = m_Direction;
	Position newPosition = m_Position;

	map[m_Position.y][m_Position.x] = FREE_POSITION_SYMBOL;
	
	if ((m_Direction == directionUp || m_IsTeleportingBack) && m_Position.y - 1 >= 0 && map[m_Position.y - 1][m_Position.x] == FREE_POSITION_SYMBOL)
	{
		newPosition.y--;
		hasMoved = true;

		if (m_IsTeleportingBack)
		{
			m_Direction = directionUp;
			m_IsTeleportingBack = false;
		}

		if (std::find(m_IteratedPosition.begin(), m_IteratedPosition.end(), newPosition) != m_IteratedPosition.end())
		{
			newPosition.y++;
			hasMoved = false;

			m_Direction = currentDirection;
			m_IsTeleportingBack = canTeleport;
		}
	}

	if (!hasMoved && (m_Direction == directionRight || m_IsTeleportingBack) && m_Position.x + 1 < map[0].size() && map[m_Position.y][m_Position.x + 1] == FREE_POSITION_SYMBOL)
	{
		newPosition.x++;
		hasMoved = true;

		if (m_IsTeleportingBack)
		{
			m_Direction = directionRight;
			m_IsTeleportingBack = false;
		}

		if (std::find(m_IteratedPosition.begin(), m_IteratedPosition.end(), newPosition) != m_IteratedPosition.end())
		{
			newPosition.x--;
			hasMoved = false;

			m_Direction = currentDirection;
			m_IsTeleportingBack = canTeleport;
		}
	}

	if (!hasMoved && (m_Direction == directionDown || m_IsTeleportingBack )&&  m_Position.y + 1 < map[0].size() && map[m_Position.y + 1][m_Position.x] == FREE_POSITION_SYMBOL)
	{
		newPosition.y++;
		hasMoved = true;

		if (m_IsTeleportingBack)
		{
			m_Direction = directionDown;
			m_IsTeleportingBack = false;
		}

		if (std::find(m_IteratedPosition.begin(), m_IteratedPosition.end(), newPosition) != m_IteratedPosition.end())
		{
			newPosition.y--;
			hasMoved = false;

			m_Direction = currentDirection;
			m_IsTeleportingBack = canTeleport;
		}
	}

	if (!hasMoved && (m_Direction == directionLeft || m_IsTeleportingBack) && m_Position.x - 1 >= 0 && map[m_Position.y][m_Position.x - 1] == FREE_POSITION_SYMBOL)
	{
		newPosition.x--;
		hasMoved = true;

		if (m_IsTeleportingBack)
		{
			m_Direction = directionLeft;
			m_IsTeleportingBack = false;
		}

		if (std::find(m_IteratedPosition.begin(), m_IteratedPosition.end(), newPosition) != m_IteratedPosition.end())
		{
			newPosition.x++;
			hasMoved = false;

			m_Direction = currentDirection;
			m_IsTeleportingBack = canTeleport;
		}
	}

	m_Position = newPosition;

	if (m_Position.x == map[0].size() - 1 && m_Position.y == map.size() - 1)
	{
		map[m_Position.y][m_Position.x] = 'P';
		std::cout << "I made it... " << '\n';
		m_CanMove = false;
		return;
	}

	if (hasMoved)
	{
		map[m_Position.y][m_Position.x] = 'P';
		m_IteratedPosition.push_back(m_Position);

		if (IsPositionReusable(m_IteratedPosition, m_Map, m_Position))
		{
			m_AvailableRoutes.push(m_Position);
		}

		std::cout << "Current Position: (" << m_Position.x << " , " << m_Position.y << ")" << '\n';
	 	return;
	}

	if (m_AvailableRoutes.size() == 0)
	{
		std::cout << "TryMoving():: Player cannot move anymore, due to no more availableRoutes..." << '\n';
		m_CanMove = false;
		return;
	}

	m_Position = m_AvailableRoutes.top();

	std::cout << "Teleported to position: (" << m_Position.x << " , " << m_Position.y << ")" << '\n';

	m_AvailableRoutes.pop();

	if (IsPositionReusable(m_IteratedPosition, m_Map, m_Position))
	{
		m_AvailableRoutes.push(m_Position);
	}

	m_IsTeleportingBack = true;
	Move();
}

bool IsPositionReusable(const std::vector<Position>& blockedPositions, const std::vector<std::string>* pointerToMap, const Position& position)
{
	if (pointerToMap == nullptr)
	{
		std::cerr << "IsPositionReusable():: pointerToMap is nullptr..." << '\n';
		return false;
	}

	const std::vector<std::string>& map = *pointerToMap;

	int counterOfRoadsFromPosition = 0;
	
	if (position.y - 1 >= 0 && map[position.y - 1][position.x] == FREE_POSITION_SYMBOL)
	{
		Position newPosition = position;
		newPosition.y--;

		if (std::find(blockedPositions.begin(), blockedPositions.end(), newPosition) == blockedPositions.end())
		{
			counterOfRoadsFromPosition++;
		}
	}

	if (position.x + 1 < map[0].size() && map[position.y][position.x + 1] == FREE_POSITION_SYMBOL)
	{
		Position newPosition = position;
		newPosition.x++;

		if (std::find(blockedPositions.begin(), blockedPositions.end(), newPosition) == blockedPositions.end())
		{
			counterOfRoadsFromPosition++;

		}
	}

	if (position.y + 1 < map.size() && map[position.y + 1][position.x] == FREE_POSITION_SYMBOL)
	{
		Position newPosition = position;
		newPosition.y++;

		if (std::find(blockedPositions.begin(), blockedPositions.end(), newPosition) == blockedPositions.end())
		{
			counterOfRoadsFromPosition++;

		}
	}

	if (position.x - 1 >= 0 && map[position.y][position.x - 1] == FREE_POSITION_SYMBOL)
	{
		Position newPosition = position;
		newPosition.x--;

		if (std::find(blockedPositions.begin(), blockedPositions.end(), newPosition) == blockedPositions.end())
		{
			counterOfRoadsFromPosition++;

		}
	}

	if (counterOfRoadsFromPosition > 0)
		return true;

	return false;
}
