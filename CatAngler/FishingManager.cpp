#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Enemy.h"
#include "Camera.h"
#include "SDL.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;

std::vector<Enemy*> enemies;

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

        Enemy* shark = new Enemy(new Properties("shark", 300, 300, 32, 32), 10);
        enemies.push_back(shark);
        
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
    if (!enemies.empty()) {
        for (unsigned int i = 0; i != enemies.size(); i++) {
            enemies[i]->setTarget(x, y, target);
            enemies[i]->update(dt);
            if (enemies[i]->getHealth() <= 0) {
                delete enemies[i];
            }
        }
    }
}

void FishingManager::draw()
{
    for (unsigned int i = 0; i != enemies.size(); i++) {
        enemies[i]->draw();
    }
    
}
