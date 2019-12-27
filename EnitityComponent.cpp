#include "EnitityComponent.h"

bool operator==(const Position& a, const Position& b)
{
	return a.x == b.x && a.y == b.y && a.direction == b.direction;
}

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

int GenerateNumber(std::mt19937& generator, const int fromSize, const int toSize)
{
	std::uniform_int_distribution<int> randomIntegerGenerator(fromSize, toSize);

	return randomIntegerGenerator(generator);
}

bool IsEntityCollidingWithObstacle(const std::vector<std::string>& map, const Position& position)
{
	return map[position.x][position.y] == FREE_POSITION_SYMBOL;
}