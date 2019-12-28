#include <iostream>
#include <vector>
#include <string>

#include "InputComponent.h"
#include "Mage.h"
#include "Sourceress.h"
#include "Enemy.h"
#include "GameLogic.h"

void InitializeGame()
{
	std::string playerClassName;
	std::vector<MapData> data = ReadMap("./maps.txt");
	SortContainerOfMaps(data);

	ReadPlayerChoiceOFClass(playerClassName);

	GameLogic gameLogic = GameLogic(playerClassName, data);
	gameLogic.Loop(data);

	std::cout << "if you want to play again pres y";
	
	char input;
	std::cin >> input;

	if (input == 'y')
	{
		return InitializeGame();
	}

	std::cout << "Thanks for playing..." << '\n';
}

int main()
{
	InitializeGame();

	//unsigned numberOfRows, numberOfCols;
	//
	//std::cout << "Enter the number of rows and then the number of cols..." << '\n';
	//std::cin >> numberOfRows >> numberOfCols;

	//std::vector<std::string> map =
	//{
	//	".#....#.",
	//	".#.....#",
	//	".#.##..#",
	//	".......#",
	//	"..##....",
	//	".#...#..",
	//	".##...##",
	//	"##......"
	//};
	
	//Sourceress sourceress(map);

	const size_t numberOfElements = 0;

	//std::vector<Enemy> enemies = GenerateEnemies(map, numberOfElements);
	//Mage mage(&map);
	//
	//while (sourceress.m_CanMove)
	//{
	//	std::cout << "Moving..." << '\n';
	//	sourceress.Move();
	//}

	//while (mage.m_CanMove && !IsPlayerCollidingWithEnemies(mage.GetPosition(), enemies))
	//{
	//	
	//	MoveEnemies(enemies);
	//	mage.TryMoving();
	//}

	return 0;
}