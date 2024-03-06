#pragma once
#include "Item.h"

class LootTable
{
public:

	void addItemToList(Item* i) { itemLists.push_back(i); }
	Item* getRandomItem();

private:
	std::vector<Item*> itemLists;
};

