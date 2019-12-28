#include "InputComponent.h"
#include "EnitityComponent.h"

#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<MapData> ReadMap(const std::string& fileName)
{
	std::vector<MapData> data;

	std::ifstream readingFromFile(fileName);

	int numberOfRows, numberOfCols;

	while (readingFromFile >> numberOfRows && readingFromFile >> numberOfCols)
	{
		if (numberOfRows <= 0 || numberOfCols <= 0)
		{
			std::cout << "ReadMap():: Input has invalid arguments..." << '\n';
			continue;
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
		if (IsMapValid(mapData))
		{
			data.push_back(mapData);
		}
	}

	return data;
}

bool IsMapValid(const MapData& entitiyMap)
{
	const size_t numberOfRows = entitiyMap.map.size();
	const size_t numberOfCols = entitiyMap.map[0].size();

	if (entitiyMap.map[0][0] != FREE_POSITION_SYMBOL || entitiyMap.map[numberOfRows - 1][numberOfCols - 1] != FREE_POSITION_SYMBOL)
	{
		return false;
	}

	if (!DoesMapHasRouteFromStartToFinish_And_WithValidSymbols(entitiyMap.map))
	{
		return false;
	}

	return true;
}


void ReadNumberOfObstacledToBeAdded(const std::vector<std::string>& map)
{
	int numberOfPlayerPlacedObstacles;
	const int numberOfPassablePositions = GetNumberOfPassableObjectsOnMap(map);

	std::cout << "Enter the number of obstacles you want to be added... " << '\n';

	do
	{
		std::cin >> numberOfPlayerPlacedObstacles;
	} 
	while (numberOfPlayerPlacedObstacles < 0 || numberOfPlayerPlacedObstacles >= numberOfPassablePositions - 2);
}