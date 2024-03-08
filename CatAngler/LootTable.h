#pragma once
#include "Item.h"
#include <unordered_map>

class LootTable
{
public:

	void addItemToList(Item* i);
	Item* getRandomItem();

private:
	std::unordered_map<int, std::vector<Item*>> itemLists;
};

