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

public:
	Enemy(const Position& position, std::vector<std::string>* map)
		: m_Position(position), m_Map(map)
	{
		if(m_Map == nullptr)
		{
			std::cerr << "Enemy():: m_Map was nullptr..." << '\n';
		}

		(*map)[position.x][position.y] = ENEMY_SYMBOL;
	}

public:
	void Move();
};


std::vector<Enemy> GenerateEnemies(std::vector<std::string>& map, const size_t numberOfElements);

void MoveEnemies(std::vector<Enemy>& enemies);

#endif
