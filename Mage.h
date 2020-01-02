#ifndef MAGE_H_GUARD
#define MAGE_H_GUARD

#include "EnitityComponent.h"
#include "PlayerCharacter.h"

#include <stack>
#include <vector>
#include <string>

bool IsPositionReusable(const std::vector<Position>& blockedPositions, const std::vector<std::string>* pointerToMap, const Position& position);

class Mage : public PlayerCharacter
{
private:
	std::stack<Position> m_AvailableRoutes;
	std::vector<Position> m_IteratedPosition;
	Direction m_Direction = directionDown;
	bool m_IsTeleportingBack = false;

	const Position& GetPosition() const
	{
		return m_Position;
	}

public:
	Mage()
	{

	}

	//Mage(std::vector<std::string>& map)
	//	:PlayerCharacter(map)
	//{
	//	m_IteratedPosition.push_back(m_Position);

	//	if (IsPositionReusable(m_IteratedPosition, m_Map, m_Position))
	//	{
	//		m_AvailableRoutes.push(m_Position);
	//	}
	//}

public:
	virtual void Move() override;
	virtual void InitializeCharacter() override;
};

#endif