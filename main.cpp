#include <iostream>
#include <vector>
#include <string>

#include "Mage.h"
#include "Sourceress.h"
#include "Enemy.h"


int main()
{
	//unsigned numberOfRows, numberOfCols;
	//
	//std::cout << "Enter the number of rows and then the number of cols..." << '\n';
	//std::cin >> numberOfRows >> numberOfCols;

	std::vector<std::string> map =
	{
		".#....#.",
		".#.....#",
		".#.##..#",
		".......#",
		"..##....",
		".#...#..",
		".##...##",
		"##......"
	};

	Sourceress sourceress(map);


	const size_t numberOfElements = 0;

	std::vector<Enemy> enemies = GenerateEnemies(map, numberOfElements);
	Mage mage(&map);
	
	int numberOfPlayerPlacedObstacles;
	const int numberOfPassablePositions = GetNumberOfPassableObjectsOnMap(map);

	//std::cout << "Enter the number of obstacles you want to add into the level..." << '\n';

	//do
	//{
	//	std::cin >> numberOfPlayerPlacedObstacles;
	//} 
	//while (numberOfPlayerPlacedObstacles < 0 || numberOfPlayerPlacedObstacles >= numberOfPassablePositions - 2);

	while (sourceress.m_CanMove)
	{
		std::cout << "Moving..." << '\n';
		sourceress.Move();
	}

	//while (mage.m_CanMove && !IsPlayerCollidingWithEnemies(mage.GetPosition(), enemies))
	//{
	//	
	//	MoveEnemies(enemies);
	//	mage.TryMoving();
	//}

	return 0;
}