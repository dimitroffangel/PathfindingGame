#ifndef SOURCERESS_H_GUARD
#define SOURCERESS_H_GUARD

#include "EnitityComponent.h"

#include <vector>
#include <string>
#include <stack>

class Sourceress
{
private:
	Position m_Position;
	std::stack<Position> m_ShortestWay;
	std::vector<std::string>* m_Map;

public:
	bool m_CanMove = true;

public:
	Sourceress(std::vector<std::string>& map)
		:m_Map(&map)
	{
		CalculateTheDistanceToEveryPosition();
	}

	void Move();

private:
	std::vector<std::vector<int>> CalculateTheDistanceToEveryPosition();
};

#endif

