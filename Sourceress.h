#ifndef SOURCERESS_H_GUARD
#define SOURCERESS_H_GUARD

#include "EnitityComponent.h"
#include "PlayerCharacter.h"

#include <vector>
#include <string>
#include <stack>

class Sourceress : public PlayerCharacter
{
private:
	std::stack<Position> m_ShortestWay;

public:
	virtual void Move() override;
	virtual void InitializeCharacter() override;

private:
	std::vector<std::vector<int>> CalculateTheDistanceToEveryPosition();
};

#endif

