#ifndef GAMELOGIC_H_GUARD
#define GAMELOGIC_H_GUARD

#include "PlayerCharacter.h"
#include "Mage.h"

#include <string>
#include <memory>

class GameLogic
{
private:
	std::unique_ptr<PlayerCharacter> m_PlayerCharacter;

public:
	GameLogic(const std::string& playerChoice, std::vector<MapData>& data);

	void Loop(std::vector<MapData>& data);
};

void InitializeGame();

#endif

