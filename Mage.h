#ifndef MAGE_H_GUARD
#define MAGE_H_GUARD

#include "EnitityComponent.h"

#include <stack>
#include <vector>
#include <string>

bool IsPositionReusable(const std::vector<Position>& blockedPositions, const std::vector<std::string>* pointerToMap, const Position& position);

class Mage
{
private:
	std::vector<std::string>* m_Map;
	Position m_Position;
	std::stack<Position> m_AvailableRoutes;
	std::vector<Position> m_IteratedPosition;
	Direction m_Direction = directionDown;
	bool m_IsTeleportingBack = false;

public:
	bool m_CanMove = true;

	const Position& GetPosition() const
	{
		return m_Position;
	}

public:
	Mage(std::vector<std::string>* map)
		:m_Map(map)
	{
		m_IteratedPosition.push_back(m_Position);

		if (IsPositionReusable(m_IteratedPosition, m_Map, m_Position))
		{
			m_AvailableRoutes.push(m_Position);
		}
	}

public:
	void TryMoving();
};

#endif