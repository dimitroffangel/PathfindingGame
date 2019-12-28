#ifndef GAMELOGIC_H_GUARD
#define GAMELOGIC_H_GUARD

#include "EnitityComponent.h"
#include "PlayerCharacter.h"
#include "Mage.h"
#include "Sourceress.h"

#include <string>
#include <memory>

class GameLogic
{
private:
	std::unique_ptr<PlayerCharacter> m_PlayerCharacter;

public:
	GameLogic(const std::string& playerChoice, std::vector<MapData>& data)
	{
		std::vector<std::string>& map = data[0].map;

		if (playerChoice == "mage")
		{
			m_PlayerCharacter = std::make_unique<Mage>();
		}

		else if (playerChoice == "sourceress")
		{
			m_PlayerCharacter = std::make_unique<Sourceress>();
		}
	}

	void Loop(std::vector<MapData>& data);
};

void InitializeGame();

#endif

