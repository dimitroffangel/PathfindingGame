#ifndef INPUTCOMPONENT_H_GUARD
#define INPUTCOMPONENT_H_GUARD

#include "EnitityComponent.h"

#include <fstream>
#include <vector>
#include <string>

using vectorOfStrings = std::vector<std::string>;

std::vector<MapData> ReadMap(const std::string& fileName);

bool IsMapValid(const MapData& entitiyMap);

void ReadNumberOfObstacledToBeAdded(const std::vector<std::string>& map);

#endif
