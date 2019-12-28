#ifndef SOURCERESS_H_GUARD
#define SOURCERESS_H_GUARD

#include "EnitityComponent.h"
#include "PlayerClass.h"

#include <vector>
#include <string>
#include <stack>

class Sourceress : public PlayerClass
{
private:
	std::stack<Position> m_ShortestWay;

public:
	Sourceress()
	{

	}

	Sourceress(std::vector<std::string>& map)
		:PlayerClass(map)
	{
		CalculateTheDistanceToEveryPosition();
	}

	virtual void Move() override;

private:
	std::vector<std::vector<int>> CalculateTheDistanceToEveryPosition();
};

#endif

