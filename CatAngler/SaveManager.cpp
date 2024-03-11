#include "SaveManager.h"

SaveManager* SaveManager::s_Instance = nullptr;

void SaveManager::saveGame(const std::string& filename, const std::unordered_map<std::string, int>& newData, bool append) {

    std::unordered_map<std::string, int> data = loadGame(filename);

    for (const auto& pair : newData) {
        data[pair.first] = pair.second; // This will insert or update the value
    }

    std::ofstream outFile(filename, std::ios::trunc); // Use trunc to overwrite the file
    if (outFile.is_open()) {
        for (const auto& pair : data) {
            outFile << pair.first << ":" << pair.second << std::endl;
        }
        outFile.close();
        std::cout << "Game saved to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

void SaveManager::saveGameover(const std::string& filename, const std::unordered_map<std::string, int>& newdata, bool append)
{
    std::unordered_map<std::string, int> data = loadGame(filename);

    for (const auto& pair : newdata) {
        data[pair.first] = pair.second; // This will insert or update the value
    }

    std::ofstream outFile(filename); // Use trunc to overwrite the file
    if (outFile.is_open()) {
        for (const auto& pair : data) {
            outFile << pair.first << ":" << pair.second << std::endl;
        }
        outFile.close();
        std::cout << "Game saved to file: " << filename << std::endl;
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
        std::cout << "Game loaded from file: " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << filename << std::endl;
    }
    return data;
}

void SaveManager::loadItems(std::unordered_map<std::string, int> loaded, std::vector<Item*> sourceItems, Inventory* playerInventory)
{
    std::unordered_map<std::string, int> loadedData = loaded;
    for (Item* i : sourceItems) {
        if (loadedData.count(i->getID()) > 0) {
            for (int n = 0; n < loadedData[i->getID()]; n++) {
                playerInventory->addItem(i);
            }
        }
    }
}
