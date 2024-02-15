#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "SDL.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;

std::vector<Enemy*> enemies;

FishingManager::FishingManager(Inventory* player_Inv, std::vector<Collider*>* colliderVec, std::vector<Fish*> fishInArea)
    : playerInventory(player_Inv), colliderVec(colliderVec)
{
	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);
}

void FishingManager::checkFishing(int x, int y, std::string map)
{
    m_Collider->set(x, y, 32, 32);

    if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), map) && x !=0) {

        Enemy* shark = new Enemy(new Properties("shark_walk", 300, 300, 32, 32), 10);
        enemies.push_back(shark);
        spawned_enemies.push_back(shark);
        colliderVec->push_back(shark->getCollider());
        
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
        }
    }
}

void FishingManager::draw()
{
    if (!enemies.empty()) {
        for (unsigned int i = 0; i != enemies.size(); i++) {
            if (enemies[i]->getHealth() > 0) {
                enemies[i]->draw();
            }   
        }
    }

    
}
