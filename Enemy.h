#ifndef ENEMY_H_GUARD
#define ENEMY_H_GUARD

#include "EnitityComponent.h"
#include <vector>
#include <string>

class Enemy
{
private:
	Position m_Position;
	std::vector<std::string>* m_Map;

	Enemy(std::vector<std::string>* map)
		: m_Map(map)
	{
		
	}

public:
	void Move();
};

#endif
