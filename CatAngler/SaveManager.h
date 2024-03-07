#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class SaveManager
{
public: 
    static SaveManager* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new SaveManager();
    }

    void saveGame(const std::string& filename, const std::unordered_map<std::string, int>& data);
    std::unordered_map<std::string, int> loadGame(const std::string& filename);

private:
    SaveManager() {}
    static SaveManager* s_Instance;
};

