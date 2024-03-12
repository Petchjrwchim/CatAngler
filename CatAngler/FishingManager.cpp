#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "SaveManager.h"
#include "TextManager.h"
#include "Menu.h"
#include "Camera.h"
#include "SDL.h"
#include "Play.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;

std::vector<Enemy*> enemies;

FishingManager::FishingManager(Inventory* player_Inv, std::vector<Collider*>* colliderVec)
    : playerInventory(player_Inv), colliderVec(colliderVec)
{

	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);

    //40
    Fish* carp = new Fish(1, "Carp", 5, "carp", 5, 40);
    Fish* crappie = new Fish(1, "Crappie", 5, "crappie", 7, 40);
    Fish* catFish = new Fish(1, "Catfish", 5, "catfish", 8, 40);
    Fish* fiddlerCrab = new Fish(1, "Fiddler crab", 5, "fiddlercrab", 10, 40);
    Fish* rainbowTrout = new Fish(1, "Rainbow Trout", 5, "rainbowtrout", 6, 30);
    //30
    Fish* wallEye = new Fish(1, "Walleye", 5, "walleye", 12, 30);
    Fish* alligatorGar = new Fish(1, "Alligator Gar", 5, "alligatorgar", 15, 30);
    Fish* pike = new Fish(1, "Pike", 5, "pike", 10, 30);
    Fish* eel = new Fish(1, "Eel", 5, "eel", 12, 30);
    //20
    Fish* redSalmon = new Fish(1, "Red salmon", 5, "redsalmon", 20, 20);
    Fish* smallMouthBass = new Fish(1, "SmallMouth Bass", 5, "smallmouthbass", 18, 20);
    Fish* largeMouthBass = new Fish(1, "LargeMouth Bass", 5, "largemouthbass", 22, 20);
    Fish* strippedBass = new Fish(1, "Stripped Bass", 5, "strippedbass", 25, 20);
    //10
    Fish* giantCrayfish = new Fish(1, "Giant crayfish", 5, "giantcrayfish", 30, 10);
    Fish* sturgeon = new Fish(1, "Sturgeon", 5, "sturgeon", 35, 10);
    Fish* featherback = new Fish(1, "Featherback", 5, "featherback", 40, 10);

    fishLists.push_back(smallMouthBass);
    fishLists.push_back(largeMouthBass);
    fishLists.push_back(catFish);
    fishLists.push_back(strippedBass);
    fishLists.push_back(fiddlerCrab);
    fishLists.push_back(rainbowTrout);
    fishLists.push_back(crappie);
    fishLists.push_back(wallEye);
    fishLists.push_back(eel);
    fishLists.push_back(pike);
    fishLists.push_back(alligatorGar);
    fishLists.push_back(sturgeon);
    fishLists.push_back(giantCrayfish);
    fishLists.push_back(carp);
    fishLists.push_back(featherback);
    fishLists.push_back(redSalmon);

    for (Item* i : fishLists) {
        fishInArea.addItemToList(i);
    }
}

void FishingManager::renderFish()
{
    Vector2D cam = Camera::GetInstance()->getPosition();

    // Use a consistent seed for rand() outside the loop
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }

    // Define the minimum distance between fish
    const int minDistance = 50; // Set this to whatever you deem appropriate

    // Check if we need to add a new fish
    while (randomFish.size() <= 10) {
        int spx = rand() % 1280;
        int spy = rand() % 960;

        // Check if the new fish is too close to existing fish
        bool tooClose = false;
        for (Collider* existingFish : randomFish) {
            int distX = std::abs(existingFish->get().x - spx);
            int distY = std::abs(existingFish->get().y - spy);
            if (distX < minDistance && distY < minDistance) {
                tooClose = true;
                break;
            }
        }

        // Only add the new fish if it's not too close to any other fish
        if (!tooClose) {
            
            Collider* f = new Collider();
            f->set(spx, spy, 32, 32);
            if (CollisionHandler::GetInstance()->mapCollision(f->get(), "Water")) {
                randomFish.push_back(f);
            }
            else {
                delete f; // Make sure to clean up if not adding to the vector
            }
        }
    }

    // Render existing fish shadows
    for (Collider* c : randomFish) {
        int f = (SDL_GetTicks() / 100) % 6;
        TextureManager::GetInstance()->drawFrame("fish_shadow", c->get().x, c->get().y , 32, 32, 1, f);
    }
}

std::vector<Enemy*>* FishingManager::getee()
{
    return &enemies;
}

void FishingManager::renderCatch(int x, int y)
{

    if (caughtFish != NULL) {
        if (caughtFish->getID() != "empty") TextureManager::GetInstance()->draw(caughtFish->getID(), x, y - 15 - caughtFishAnim, 32, 32);
        if (caughtFish->getID() == "empty") TextManager::GetInstance()->renderText("Inventory full!", x - 20, y - 15 - caughtFishAnim, "assets/fonts/PixelifySans.ttf", 15, {255,20,20});
        caughtFishAnim += 0.5f;
        if (caughtFishAnim > 20) {
            caughtFishAnim = 0.f;
            caughtFish = NULL;
        }
    }
}

void FishingManager::checkFishing(int x, int y, std::string map)
{

    srand(time(NULL));
    m_Collider->set(x, y, 32, 32);

    int chance = rand() % 10;

    if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), map) && x !=0) {
        randomFish.clear();
        if ( chance > 2) {
            if (playerInventory != nullptr) {
                if (std::count(playerInventory->getItems().begin(), playerInventory->getItems().end(), nullptr) != 0) {
                    caughtFish = fishInArea.getRandomItem();
                    playerInventory->addItem(caughtFish);                  
                    std::unordered_map<std::string, int> loadedData = SaveManager::GetInstance()->loadGame("savegame" + Engine::GetInstance()->getPlayerSlot() + ".txt");
                    std::cout << loadedData[caughtFish->getID() + "caught"] << std::endl;
                    std::unordered_map<std::string, int> savefish = { {caughtFish->getID() + "caught", loadedData[caughtFish->getID() + "caught"] + 1} };
                    SaveManager::GetInstance()->saveGame("savegame" + Engine::GetInstance()->getPlayerSlot() + ".txt", savefish);
                }
                else {
                    Fish* empty = new Fish(1, "empty", 5, "empty", 0, 0);
                    caughtFish = empty;
                }
                
            }
        }
        else {
            int chance = rand() % 10;
            caughtFish = NULL;
            Enemy* enemy;
            if (chance > 3) {
                enemy = new Enemy(new Properties("shark", x, y, 32, 32), 10, 4);
            }
            else {
                enemy = new Enemy(new Properties("squid", x, y, 64, 64), 20, 7);
            }
            enemies.push_back(enemy);// for render enemies in this class in this class
            spawned_enemies.push_back(enemy); //for checking with sword
            colliderVec->push_back(enemy->getCollider());
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
