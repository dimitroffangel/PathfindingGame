#include <iostream>
#include <vector>
#include <string>

#include "Mage.h"
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

	const size_t numberOfElements = 4;

	std::vector<Enemy> enemies = GenerateEnemies(map, numberOfElements);
	Mage mage(&map);
	
	while (mage.m_CanMove)
	{
		MoveEnemies(enemies);
		mage.TryMoving();
	}

	return 0;
}