#include "SaveManager.h"

SaveManager* SaveManager::s_Instance = nullptr;

void SaveManager::saveGame(const std::string& filename, const std::unordered_map<std::string, int>& data)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : data) {
            file << pair.first << ":" << pair.second << std::endl;
        }
        std::cout << "Game saved successfully!" << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

std::unordered_map<std::string, int> SaveManager::loadGame(const std::string& filename)
{
    std::unordered_map<std::string, int> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                int value = std::stoi(line.substr(pos + 1));
                data[key] = value;
            }
        }
        std::cout << "Game loaded" << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << filename << std::endl;
    }
    return data;
}
