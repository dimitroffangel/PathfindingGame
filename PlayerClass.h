#ifndef PLAYERCLASS_H_GUARD
#define PLAYERCLASS_H_GUARD

#include "EnitityComponent.h"

class PlayerClass
{
protected:
	Position m_Position;
	std::vector<std::string>* m_Map;
	bool m_CanMove = true;


public:
	bool CanMove() const
	{
		return m_CanMove;
	}

	const Position& GetPosition() const
	{
		return m_Position;
	}

	void SetMap(std::vector<std::string>& map)
	{
		m_Map = &map;
	}

	PlayerClass()
	{

	}

	PlayerClass(std::vector<std::string>& map)
		:m_Map(&map)
	{

	}

	virtual ~PlayerClass()
	{

	}

	virtual void Move() = 0;
};

#endif

