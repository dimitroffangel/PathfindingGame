#include "GameLogic.h"
#include "Enemy.h"
#include "InputComponent.h"
#include "Sourceress.h"

GameLogic::GameLogic(const std::string& playerChoice)
{
	if (playerChoice == "mage")
	{
		m_PlayerCharacter = std::make_unique<Mage>();
	}

	else if (playerChoice == "sourceress")
	{
		m_PlayerCharacter = std::make_unique<Sourceress>();
	}
}

void GameLogic::Loop(std::vector<MapData>& data)
{
	const size_t dataSize = data.size();

	for (int i = 0; i < dataSize; i++)
	{
		std::vector<std::string>& map = data[i].map;

		auto enemies = GenerateEnemies(map, data[i].numberOfMonsters);

		PrintMap(map);
		m_PlayerCharacter->SetMap(map);
		m_PlayerCharacter->InitializeCharacter();

		{
			std::vector<Position> addedObstacles = ReadNumberOfObstacledToBeAdded(map);

			if (!DoesMapHasRouteFromStartToFinish(map))
			{
				i--;

				for (const auto& addedObstaclePostion : addedObstacles)
				{
					map[addedObstaclePostion.y][addedObstaclePostion.x] = FREE_POSITION_SYMBOL;
				}

				continue;
			}
		}

		bool isPlayerCollidingWithEnemies = false;

		while (m_PlayerCharacter->CanMove() && !isPlayerCollidingWithEnemies)
		{
			MoveEnemies(enemies);
			m_PlayerCharacter->Move();
			isPlayerCollidingWithEnemies = IsPlayerCollidingWithEnemies(m_PlayerCharacter->GetPosition(), enemies);
			PrintMap(map);
		}

		const Position& playerPostion = m_PlayerCharacter->GetPosition();

		if (playerPostion.x == map[0].size() - 1 && playerPostion.y == map.size() - 1)
		{
			std::cout << "You finished the level..." << '\n';
			std::cout << "Starting the new one..." << '\n';
			continue;
		}

		if (isPlayerCollidingWithEnemies || !m_PlayerCharacter->CanMove())
		{
			std::cout << "Enemy collided with your character; Game Over..." << '\n';
			return;
		}
	}

	std::cout << "You won..." << '\n';
	
}

void InitializeGame()
{
	std::string playerCharacterName;
	
	std::vector<MapData> data = ReadMap("./maps.txt");
	SortContainerOfMaps(data);

	ReadPlayerChoiceOFClass(playerCharacterName);

	GameLogic gameLogic = GameLogic(playerCharacterName);
	gameLogic.Loop(data);

	std::cout << "if you want to play again press y";

	char input;
	std::cin >> input;

	if (input == 'y')
	{
		return InitializeGame();
	}

	std::cout << "Thanks for playing..." << '\n';
}

void TestGame()
{
	std::string playerCharacterName = "sourceress";

	std::ifstream readingFromFile("./UnitTests.txt");
	
	int numberOfRows, numberOfCols;

	readingFromFile >> numberOfRows;
	readingFromFile >> numberOfCols;
	
	if (numberOfRows <= 0 || numberOfCols <= 0)
	{
		std::cout << "TestGame():: Input has invalid arguments..." << '\n';
		return;
	}

	MapData mapData;

	// read the map
	mapData.map = vectorOfStrings(numberOfRows);
	std::string currentRow;

	for (size_t i = 0; i < numberOfRows; i++)
	{
		readingFromFile >> currentRow;
		mapData.map[i] = currentRow;
	}

	// read the number of monsters
	readingFromFile >> mapData.numberOfMonsters;


	// check is the map valid
	if (!IsMapValid(mapData))
	{
		std::cout << "Map was not valid...";
		return;
	}

	std::vector<Enemy> enemies;
	enemies.reserve(mapData.numberOfMonsters);

	for (size_t i = 0; i < mapData.numberOfMonsters; i++)
	{
		Position enemyPosition;
		readingFromFile >> enemyPosition.x;
		readingFromFile >> enemyPosition.y;

		enemies.push_back(Enemy(enemyPosition, &mapData.map));
	}

	GameLogic logic = GameLogic(playerCharacterName);

	PrintMap(mapData.map);
	
	std::unique_ptr<PlayerCharacter> m_PlayerCharacter;

	if (playerCharacterName == "mage")
	{
		m_PlayerCharacter = std::make_unique<Mage>();
	}

	else if (playerCharacterName == "sourceress")
	{
		m_PlayerCharacter = std::make_unique<Sourceress>();
	}

	m_PlayerCharacter->SetMap(mapData.map);
	m_PlayerCharacter->InitializeCharacter();

	bool isPlayerColliding = false;
	int turn = 0;

	while (m_PlayerCharacter->CanMove() && !isPlayerColliding)
	{
		MoveEnemies(enemies);
		turn++;
		std::cout << "Turn " << turn << " | " << "moving enemies first";
		PrintMap(mapData.map);
		m_PlayerCharacter->Move();
		isPlayerColliding = IsPlayerCollidingWithEnemies(m_PlayerCharacter->GetPosition(), enemies);
		PrintMap(mapData.map);
	}

	std::cout << "if you want to play again press y";
}
