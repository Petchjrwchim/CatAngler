#include "Play.h"
#include "SaveManager.h"
#include "TextManager.h"
#include "Cat.h"
#include "Menu.h"
#include "Engine.h"
#include "Camera.h"
#include "Timer.h"
#include "FishingManager.h"
#include "Input.h"
#include "Tile.h"
#include "Shop.h"

Cat* cat = nullptr;
Shop shop;
Tile* m_Tile;
Vector2D cam = Camera::GetInstance()->getPosition();
Play* Play::s_Instance = nullptr;

bool Play::init()
{
	m_Tile = Tile::GetInstance(); // This should assign to the class member
	if (!m_Tile->load("yourMapID", "assets/images/map2.json")) {
		std::cerr << "Failed to load the map." << std::endl;
		return false;
	}
	
	std::cout << Engine::GetInstance()->getPlayerSlot() << std::endl;

	loadedData = SaveManager::GetInstance()->loadGame("savegame" + Engine::GetInstance()->getPlayerSlot() + ".txt");
	if (loadedData["Health"] == NULL || loadedData["Health"] <= 0) loadedData = SaveManager::GetInstance()->loadGame("defaultsave.txt");

	int tilesize = 32;
	int width = 40 * tilesize;
	int height = 30 * tilesize;

	Camera::GetInstance()->setSceneLimit(width, height);
	cat = new Cat(new Properties("cat", loadedData["PosX"], loadedData["PosY"], 32, 32), loadedData["Health"]);
	cat->setCoin(loadedData["Coin"]);
	cat->setDay(loadedData["Day"]);

	Shop();
	shop.setPlayercoin(loadedData["Coin"]);
	Camera::GetInstance()->setTarget(cat->getOrigin());

	for (Item* i : FishingManager::GetInstance()->getFishLists()) {
		if (loadedData[i->getID() + "x"] != NULL) {
			unlockFish.push_back({ loadedData[i->getID() + "x"], loadedData[i->getID() + "y"] });
			gameData.insert({ i->getID() + "x",loadedData[i->getID() + "x"] });
			gameData.insert({ i->getID() + "y",loadedData[i->getID() + "y"] });
		}
	}

	SaveManager::GetInstance()->loadItems(loadedData, shop.getShopItems(), cat->getInventory());
	SaveManager::GetInstance()->loadItems(loadedData, FishingManager::GetInstance()->getFishLists(), cat->getInventory());

	initButton();
	
	return true;
}

bool Play::exit()
{
	
	std::unordered_map<std::string, int> f = SaveManager::GetInstance()->loadGame("savegame" + Engine::GetInstance()->getPlayerSlot() + ".txt");
	gameData.insert({ "Health", cat->getHealth() }); 
	gameData.insert({ "Coin", cat->getCoin() });
	gameData.insert({ "PosX", cat->getTX() });
	gameData.insert({"PosY", cat->getTY()});
	gameData.insert({ "Day", cat->getDay() });

	for (Item* i : cat->getInventory()->getItems()) {
		if (i != NULL && i->getQuantity() > 0) gameData.insert({i->getID(), i->getQuantity()});
	}

	for (Item* i : FishingManager::GetInstance()->getFishLists()) {
		gameData.insert({ i->getID() + "caught", f[i->getID() + "caught"] });
		std::cout << i->getID()  << f[i->getID() + "caught"] << std::endl;
	}

	for (const auto& pair : gameData) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	
	SaveManager::GetInstance()->saveGameover("savegame" + Engine::GetInstance()->getPlayerSlot() + ".txt", gameData);
	std::cout << "Game close" << std::endl;

	//FishingManager::GetInstance()->getEnemies().clear();

	cat = nullptr;

	loadedData = {};
	gameData = {};

	return true;
}

void Play::update()
{
	if (IsPause) Input::GetInstance()->setCurrentWindow("pause");
	if (IsCollection) {
		Input::GetInstance()->setCurrentWindow("fishcollection");
	}
	if (!IsPause && !IsCollection) {
		Input::GetInstance()->setCurrentWindow("play");
		cam = Camera::GetInstance()->getPosition();
		float dt = Timer::GetInstance()->getDeltaTime();

		cat->update(dt);

		if (cat->getIs_Shopping() && !shop.get_IsVisible()) {
			shop.toggleShopUI();
		}
		else if (!cat->getIs_Shopping() && shop.get_IsVisible()) {
			shop.toggleShopUI();
		}
		
		cat->setCoin(shop.getShopCoin());
		shop.setPlayercoin(cat->getCoin());
		shop.setPlayerInventory(cat->getInventory());
		shop.update(cam.X, cam.Y);

		Camera::GetInstance()->update(dt);

		int row = 0;
		int col = 0;
		for (Item* i : FishingManager::GetInstance()->getFishLists()) {
			for (Item* j : cat->getInventory()->getItems()) {
				if (j != NULL && i->getID() == j->getID()) {
					std::pair<int, int> a(row, col);
					unlockFish.push_back(a);
					gameData.insert({ i->getID() + "x", row });
					gameData.insert({ i->getID() + "y", col });
				}
			}
			Input::GetInstance()->addButton(280 + 64 * col, 158 + 64 * row, 48, 48, "fishcollection", [i]() {
				}, [i, this, col, row]() {
					this->fish = i;
					this->show = true;
					});
			col++;
			if (col == 4) {
				row++;
				col = 0;
			}
		}
	}
}

void Play::render()
{
	
	cam = Camera::GetInstance()->getPosition();
	if (!cat->getInteract()) {
		m_Tile->render("Floor");
		m_Tile->render("House");
	}
	else {
		m_Tile->render("Indoor");
		m_Tile->render("Shop");
	}

	cat->draw();
	cat->equip();

	if (!cat->getInteract()) {
		m_Tile->render("Tree");
		//TextureManager::GetInstance()->draw("night", cam.X, cam.Y, 80, 60, SDL_FLIP_NONE, 10);
	}
	else {
		TextureManager::GetInstance()->draw("shopkeeper", 445, 520, 36, 36);
		m_Tile->render("Shopkeeper");
	}

	cat->drawInv();

	if (shop.get_IsVisible()) {
		shop.render(Engine::GetInstance()->GetRenderer());
	}

	cam = Camera::GetInstance()->getPosition();

	TextureManager::GetInstance()->draw("fishcollection", cam.X + 708, cam.Y + 60, 32, 32, SDL_FLIP_NONE, 1.5);

	TextureManager::GetInstance()->draw("pause_button", cam.X + 700, cam.Y, 32, 32, SDL_FLIP_NONE, 2);
	if (IsPause) {
		TextureManager::GetInstance()->draw("badge", 314 + cam.X, 148 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);
		TextureManager::GetInstance()->draw("badge", 314 + cam.X, 248 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);
		TextureManager::GetInstance()->draw("badge", 314 + cam.X, 348 + cam.Y, 64, 64, SDL_FLIP_NONE, 3);

		TextManager::GetInstance()->renderText("Resume", 385 + cam.X, 230 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 25);
		TextManager::GetInstance()->renderText("Settings", 365 + cam.X, 330 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 25);
		TextManager::GetInstance()->renderText("Return", 385 + cam.X, 430 + cam.Y, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 25);

	}

	if (IsCollection) {
		renderCollection();
	}
	
	//Input::GetInstance()->renderButtons(Engine::GetInstance()->GetRenderer());
}

void Play::initButton()
{
	Vector2D cam = Camera::GetInstance()->getPosition();

	Input::GetInstance()->addButton(cam.X + 705, cam.Y + 10, 54, 40, "play", [this]() {
		std::cout << "pause" << std::endl;
		this->IsPause = true;
		}, []() {});

	Input::GetInstance()->addButton(cam.X + 708, cam.Y + 60, 48, 48, "play", [this]() {
		std::cout << "collection" << std::endl;
		//Input::GetInstance()->deleteButton(24); // delete excess button
		this->IsCollection = !IsCollection;
		}, []() {});
	Input::GetInstance()->addButton(cam.X + 708, cam.Y + 60, 48, 48, "fishcollection", [this]() {
		std::cout << "collection" << std::endl;
		Input::GetInstance()->deleteButton(46); // delete excess button
		this->IsCollection = !IsCollection;
		}, []() {});

	Input::GetInstance()->addButton(cam.X + 705, cam.Y + 10, 54, 40, "pause", [this]() {
		std::cout << "unpause" << std::endl;
		this->IsPause = false;
		}, []() {});

	Input::GetInstance()->addButton(300, 220, 200, 50, "pause", [this]() {
		std::cout << "resume" << std::endl;
		this->IsPause = false;
		}, [this]() {
			});
	Input::GetInstance()->addButton(300, 320, 200, 50, "pause", [this]() {
		}, [this]() {
			});

	Input::GetInstance()->addButton(300, 420, 200, 50, "pause", [this]() {
		std::cout << "return" << std::endl;
		this->exit();
		this->IsPause = false;
		Input::GetInstance()->setCurrentWindow("menu");
		Engine::GetInstance()->changeGameState("menu");
		}, [this]() {
			});
}

void Play::openMenu()
{
}

void Play::pauseGame()
{
}

void Play::renderCollection()
{

	Input::GetInstance()->setCurrentWindow("fishcollection");

	TextureManager::GetInstance()->draw("fishcollection_bg", cam.X + 80, cam.Y - 40, 128, 128, SDL_FLIP_NONE, 5);
	TextureManager::GetInstance()->draw("lock", cam.X + 272, cam.Y + 150, 128, 128, SDL_FLIP_NONE, 2);
	if (!unlockFish.empty()) {
		for (std::pair it : unlockFish) {
			TextureManager::GetInstance()->drawFrame("unlock", cam.X + 272 + 64 * it.second, cam.Y + 150 + 64 * it.first, 32, 32, it.first + 1, it.second, SDL_FLIP_NONE, 2);
		}
	}
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (show && fish != NULL) {
		loadedData = SaveManager::GetInstance()->loadGame("savegame" + Engine::GetInstance()->getPlayerSlot() + ".txt");
		gameData.insert({ fish->getID() + "caught", loadedData[fish->getID() + "caught"] });
		
		TextureManager::GetInstance()->draw("button", cam.X + x - 20, cam.Y + y - 60, 64, 64, SDL_FLIP_NONE, 3);
		TextManager::GetInstance()->renderText( fish->getName().c_str(), cam.X + x + 10, cam.Y + y + 10, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 15);
		TextManager::GetInstance()->renderText("caught: ", cam.X + x + 20, cam.Y + y + 25, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 15);
		std::stringstream strm;
		strm << loadedData[fish->getID() + "caught"];
		TextManager::GetInstance()->renderText(strm.str().c_str(), cam.X + x + 20, cam.Y + y + 45, "assets/fonts/VCR_OSD_MONO_1.001.ttf", 15);
		fish = NULL;
	}

}