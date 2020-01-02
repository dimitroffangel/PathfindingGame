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
		if (numberOfRows < 0 || numberOfCols < 0)
		{
			std::cout << "ReadMap():: Input has invalid arguments..." << '\n';
			continue;
		}

		if (numberOfRows == 0 && numberOfCols == 0)
		{
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
	const size_t numberOFFreePositions = GetNumberOfPassableObjectsOnMap(entitiyMap.map);

	if (entitiyMap.numberOfMonsters > 0 && entitiyMap.numberOfMonsters >= numberOFFreePositions - 1)
	{
		return false;
	}

	if (entitiyMap.map[0][0] != FREE_POSITION_SYMBOL || entitiyMap.map[numberOfRows - 1][numberOfCols - 1] != FREE_POSITION_SYMBOL)
	{
		return false;
	}

	if (!IsMapWithValidSymbols(entitiyMap.map) || !DoesMapHasRouteFromStartToFinish(entitiyMap.map))
	{
		return false;
	}

	return true;
}


std::vector<Position> ReadNumberOfObstacledToBeAdded(std::vector<std::string>& map)
{
	
	int numberOfPlayerPlacedObstacles;
	const int numberOfPassablePositions = GetNumberOfPassableObjectsOnMap(map);

	if (numberOfPassablePositions <= 2)
	{
		std::cout << "There is no free position where to add an obstacle..." << '\n';
		return std::vector<Position>();
	}

	do
	{
		std::cout << "Enter the number of obstacles you want to be added, where the number must be between 0 and " << numberOfPassablePositions << "... " << '\n';
		std::cin >> numberOfPlayerPlacedObstacles;
	} 

	while (numberOfPlayerPlacedObstacles < 0 || (numberOfPlayerPlacedObstacles >= numberOfPassablePositions - 2));

	if (numberOfPlayerPlacedObstacles == 0)
	{
		return std::vector<Position>();
	}

	std::vector<Position> addedObstaclesPositions;
	addedObstaclesPositions.reserve(numberOfPassablePositions);
	Position newObstaclePosition;

	std::cout << "Enter positions, you want to block..." << '\n';
	for (size_t i = 0; i < numberOfPlayerPlacedObstacles; i++)
	{
		std::cout << "Enter the positions";
		do
		{
			std::cout << "X can be from 0 to " << map[0].size() - 1 << "Y can be from 0 to " << map.size() - 1 << ": ";
			std::cin >> newObstaclePosition.x >> newObstaclePosition.y;

		} 
		while (newObstaclePosition.x < 0 || newObstaclePosition.y < 0 || newObstaclePosition.x >= map[0].size() || newObstaclePosition.y >= map.size() 
				|| map[newObstaclePosition.y][newObstaclePosition.x] == ENEMY_SYMBOL || map[newObstaclePosition.y][newObstaclePosition.x] == OBSTACLE_SYMBOL || 
				(newObstaclePosition.x == 0 && newObstaclePosition.y == 0) || (newObstaclePosition.x == map[0].size() - 1 && newObstaclePosition.y == map.size() - 1));
	
		map[newObstaclePosition.y][newObstaclePosition.x] = PLAYER_OBSTACLE_SYMBOL;
		addedObstaclesPositions.push_back(newObstaclePosition);
	}

	return addedObstaclesPositions;
}

void ReadPlayerChoiceOFClass(std::string& playerClass)
{
	std::cout << "Type the class you want to play with for the remainder of the session... You have choice between a 'mage' or a 'sourceress'... " << '\n';

	do
	{
		std::cin >> playerClass;
	} while (playerClass != "mage" && playerClass != "sourceress");
}
