#ifndef GAMELOGIC_H_GUARD
#define GAMELOGIC_H_GUARD

#include "EnitityComponent.h"
#include "PlayerClass.h"
#include "Mage.h"
#include "Sourceress.h"

#include <string>
#include <memory>

class GameLogic
{
private:
	std::unique_ptr<PlayerClass> m_PlayerClass;

public:
	GameLogic(const std::string& playerChoice, std::vector<MapData>& data)
	{
		std::vector<std::string>& map = data[0].map;

		if (playerChoice == "mage")
		{
			m_PlayerClass = std::make_unique<Mage>();
		}

		else if (playerChoice == "sourceress")
		{
			m_PlayerClass = std::make_unique<Sourceress>();
		}
	}

	void Loop(std::vector<MapData>& data);
};

#endif

