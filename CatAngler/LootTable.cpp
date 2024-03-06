#include "LootTable.h"

Item* LootTable::getRandomItem()
{
    srand(time(NULL));
    int chance = rand() % 100;
    int total;
    for (Item* i : itemLists) {
        total += i->getDropChance();
    }


    return nullptr;
}
