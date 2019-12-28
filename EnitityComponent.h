#ifndef ENTITYCOMPONENT_H_GUARD
#define ENTITYCOMPONENT_H_GUARD

#include <iostream>
#include <random>

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
const char FREE_POSITION_SYMBOL = '.';
const char ENEMY_SYMBOL = 'E';

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

int GenerateNumber(std::mt19937& generator, const int fromSize, const int toSize);

bool IsEntityCollidingWithObstacle(const std::vector<std::string>& map, const Position& position);

int GetNumberOfPassableObjectsOnMap(const std::vector<std::string>& map);

void AddObstacleToMap(std::vector<std::string>& map, int x, int y);

#endif