#include "LootTable.h"

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
