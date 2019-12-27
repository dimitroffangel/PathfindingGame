#pragma once
#include "EnitityComponent.h"

#include <stack>
#include <vector>
#include <string>

class Mage
{
private:
	Position m_Position;
	std::stack<Position> m_AvailableRoutes;
	std::vector<Position> m_IteratedPosition;
	Direction m_Direction;
	const std::vector<std::string>* m_Map;

	Mage(const std::vector<std::string>* map)
		:m_Map(map), m_Direction(directionDown)
	{
		if (IsPositionReusable(map, m_Position))
		{
			m_AvailableRoutes.push(m_Position);
		}

	}

public:
	void TryMoving();
};

bool IsPositionReusable(const std::vector<std::string>* pointerToMap, const Position& position);