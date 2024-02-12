#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Enemy.h"
#include "Camera.h"
#include "SDL.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;

Enemy* shark = nullptr;

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

        
        shark = new Enemy(new Properties("slot", 300, 300, 32, 32));

        std::cout << "Got fish!" << std::endl;
        Fish* caughtFish = new Fish( 1, "Salmon", 5, "Common", "fish");
        if (playerInventory != nullptr) {
            std::cout << "add fish!" << std::endl;
            playerInventory->addItem(caughtFish);
        }
    }
}

void FishingManager::update(float dt, int x, int y, SDL_Rect target)
{
    if (shark != nullptr) {
        shark->setTarget(x, y, target);
        shark->update(dt);
        if (shark->getHealth() == 0) {
            delete shark;
        }
    }
}

void FishingManager::draw()
{
    if (shark != nullptr) {
        shark->draw();
    }
    
}
