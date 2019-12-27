#pragma once

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

enum Direction {
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

Direction GetReversedDirection(Direction direction)
{
	if (direction == directionUp)
	{
		return directionDown;
	}

	if (direction == directionDown)
	{
		return directionUp;
	}

	if (direction == directionLeft)
	{
		return directionRight;
	}

	if (direction == directionRight)
	{
		return directionLeft;
	}

	return direction;
}

bool MovePosition(Position& position, Direction direction)
{
	if (direction == directionNone)
	{
		std::cout << "MovePosition():: direction was none..." << '\n';
		return false;
	}

	if (direction == directionUp)
	{
		position.y -= 1;
		return true;
	}

	else if (direction == directionRight)
	{
		position.x += 1;
		return true;
	}

	else if (direction == directionDown)
	{
		position.y += 1;
		return true;
	}

	else if (direction == directionLeft)
	{
		position.x -= 1;
		return true;
	}
}