#ifndef PLAYERCHARACTER_H_GUARD
#define PLAYERCHARACTER_H_GUARD

#include "EnitityComponent.h"

class PlayerCharacter
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
		// reset player position
		m_Position.x = 0;
		m_Position.y = 0;
		m_CanMove = true;

		m_Map = &map;
	}

	PlayerCharacter()
	{

	}

	PlayerCharacter(std::vector<std::string>& map)
		:m_Map(&map)
	{

	}

	virtual ~PlayerCharacter()
	{

	}

	virtual void Move() = 0;
	virtual void InitializeCharacter() = 0;
};

#endif

