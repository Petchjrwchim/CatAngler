#include "LootTable.h"

std::unordered_map<int, std::vector<Item*>>::iterator itr;

void LootTable::addItemToList(Item* i)
{
    bool found = false;
    for (itr = itemLists.begin(); itr != itemLists.end(); ++itr) {
        if (i->getDropChance() == itr->first) {
            itr->second.push_back(i);
            found = true;
        }
    }
    if (!found) {
        itemLists.insert({ i->getDropChance(), {i}});
    }
    
}

Item* LootTable::getRandomItem()
{
    srand(time(NULL));
    
    
    int total = 0;
    for (itr = itemLists.begin(); itr != itemLists.end(); ++itr) {
        total += itr->first;
    }

    int chance = rand() % total;
    
    for (itr = itemLists.begin(); itr != itemLists.end(); ++itr) {
        if (chance <= itr->first) {
            int r = rand() % itr->second.size();
            std::cout << "add " << itr->second[r]->getName() << std::endl;
            return itr->second[r];
        }
        else {
            chance -= itr->first;
        }
    }


    return nullptr;
}