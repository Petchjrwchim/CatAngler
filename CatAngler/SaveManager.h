#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Inventory.h"
#include <unordered_map>

class SaveManager
{
public: 
    static SaveManager* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new SaveManager();
    }

    void saveGame(const std::string& filename, const std::unordered_map<std::string, int>& data, bool append = false);
    void saveGameover(const std::string& filename, const std::unordered_map<std::string, int>& data);
    std::unordered_map<std::string, int> loadGame(const std::string& filename);
    void loadItems(std::unordered_map<std::string, int> loaded, std::vector<Item*> sourceItems, Inventory* playerInventory);

private:
    SaveManager() {}
    static SaveManager* s_Instance;
};

