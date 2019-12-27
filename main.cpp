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


	Mage mage(&map);

	while (mage.m_CanMove)
	{
		mage.TryMoving();
	}


	return 0;
}