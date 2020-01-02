#ifndef MAGE_H_GUARD
#define MAGE_H_GUARD

#include "EnitityComponent.h"
#include "PlayerCharacter.h"

#include <stack>
#include <vector>
#include <string>

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
	virtual void Move() override;
	virtual void InitializeCharacter() override;
};

bool IsPositionReusable(const std::vector<Position>& blockedPositions, const std::vector<std::string>* pointerToMap, const Position& position);

#endif