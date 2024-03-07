#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "SDL.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;

std::vector<Enemy*> enemies;

FishingManager::FishingManager(Inventory* player_Inv, std::vector<Collider*>* colliderVec)
    : playerInventory(player_Inv), colliderVec(colliderVec)
{
	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);

}

void FishingManager::checkFishing(int x, int y, std::string map)
{
    srand(time(NULL));
    m_Collider->set(x, y, 32, 32);

    int chance = rand() % 10;

    if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), map) && x !=0) {

        if ( chance > 10) {
            std::cout << "Got fish!" << std::endl;
            Fish* caughtFish = new Fish(1, "Salmon", 5, "Common", "fish", 10);
            if (playerInventory != nullptr) {
                std::cout << "add fish!" << std::endl;
                playerInventory->addItem(caughtFish);
            }
        }
        else {
            Enemy* shark = new Enemy(new Properties("shark", x, y, 32, 32), 10, 4);
            Enemy* squid = new Enemy(new Properties("squid", x, y, 64, 64), 10, 7);
            enemies.push_back(squid);
            colliderVec->push_back(squid->getCollider());
        }

    }
}


void FishingManager::update(float dt, int x, int y, int* health,SDL_Rect target)
{
    if (!enemies.empty()) {
        for (unsigned int i = 0; i < enemies.size(); i++) {
            enemies[i]->setTarget(x, y, health, target);
            enemies[i]->setColliderVec(*colliderVec);
            enemies[i]->update(dt);
        }
    }
}

void FishingManager::draw()
{
    if (!enemies.empty()) {
        for (unsigned int i = 0; i < enemies.size(); i++) {
            enemies[i]->draw();
            if (enemies[i]->getHealth() < 1) {
                enemies[i]->getCollider()->set(0, 0, 0, 0);
                enemies.erase(enemies.begin() + i, enemies.begin() + i + 1);
            }
        }
    }

    
}
