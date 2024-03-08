#include "LootTable.h"

void LootTable::addItemToList(Item* i)
{
    std::unordered_map<int, std::vector<Item*>>::iterator itr;
    for (itr = itemLists.begin(); itr != itemLists.end(); ++itr) {
        if (i->getDropChance() == itr->first) {

        }
    }
    
}

Item* LootTable::getRandomItem()
{
    srand(time(NULL));
    
    int chance = rand() % 100;
    int total = 0;

    for (Item* i : itemLists) {
        total += i->getDropChance();
    }




    return nullptr;
}