#include <iostream>
#include <vector>
#include <string>

#include "InputComponent.h"
#include "Mage.h"
#include "Sourceress.h"
#include "Enemy.h"


int main()
{
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


	std::vector<MapData> data = ReadMap("./maps.txt");

	auto predicate = [data](const MapData& lhs, const MapData& rhs)
	{
		const size_t lhsMapSize = lhs.map.size() * lhs.map[0].size();
		const size_t rhsMapSize = rhs.map.size() * rhs.map[0].size();

		if (lhsMapSize == rhsMapSize)
		{
			return lhs.numberOfMonsters < rhs.numberOfMonsters;
		}

		return lhsMapSize < rhsMapSize;
	};

	std::sort(data.begin(), data.end(), predicate);

	//Sourceress sourceress(map);

	//const size_t numberOfElements = 0;

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