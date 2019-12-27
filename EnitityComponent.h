#ifndef ENTITYCOMPONENT_H_GUARD
#define ENTITYCOMPONENT_H_GUARD

#include <iostream>

//#include<vector>
//
//class Actor
//{
//	std::vector<IComponent*> m_Components;
//};
//
//// empty class
//class IComponent
//{
//	
//};
//
//class MoveComponent : protected IComponent
//{
//	int x, y;
//};

const char OBSTACLE_SYMBOL = '#';

enum Direction 
{
	directionNone = 0,
	directionUp = 1 << 0,
	directionDown = 1 << 1,
	directionLeft = 1 << 2,
	directionRight = 1 << 3,
};

struct Position
{
	int x = 0, y = 0;
	Direction direction = directionNone;
};

bool operator==(const Position& a, const Position& b);

Direction GetReversedDirection(Direction direction);

bool MovePosition(Position& position, Direction direction);

#endif