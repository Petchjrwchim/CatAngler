#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "SDL.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;


FishingManager::FishingManager(Inventory* player_Inv, std::vector<Fish*> fishInArea)
    : playerInventory(player_Inv)
{
	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);
}

void FishingManager::checkFishing(int x, int y, std::string map)
{
    m_Collider->set(x, y, 32, 32);

    if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), map)) {
        std::cout << "Got fish!" << std::endl;
        Fish* caughtFish = new Fish( 1, "Salmon", 5, "Common", "fish");
        if (playerInventory != nullptr) {
            std::cout << "add fish!" << std::endl;
            playerInventory->addItem(caughtFish);
        }
    }
}

void FishingManager::update(bool input, int x, int y)
{

}
