#include "Play.h"
#include "SaveManager.h"
#include "Cat.h"
#include "Engine.h"
#include "Camera.h"
#include "Timer.h"
#include "Input.h"
#include "Tile.h"
#include "Shop.h"

Cat* cat = nullptr;
Shop* shop = nullptr;
Tile* m_Tile;
Vector2D cam = Camera::GetInstance()->getPosition();

bool Play::init()
{
	m_Tile = Tile::GetInstance(); // This should assign to the class member
	if (!m_Tile->load("yourMapID", "assets/images/map2.json")) {
		std::cerr << "Failed to load the map." << std::endl;
		return false;
	}

	std::unordered_map<std::string, int> loadedData = SaveManager::GetInstance()->loadGame("savegame.txt");

	int tilesize = 32;
	int width = 40 * tilesize;
	int height = 30 * tilesize;

	Camera::GetInstance()->setSceneLimit(width, height);
	cat = new Cat(new Properties("cat", loadedData["PosX"], loadedData["PosY"], 32, 32), loadedData["Health"]);
	cat->setCoin(loadedData["Coin"]);

	Camera::GetInstance()->setTarget(cat->getOrigin());
	shop = new Shop(cat->getInventory(), cat->getCoin());

	initButton();

	return true;
}

bool Play::exit()
{
	std::unordered_map<std::string, int> gameData = {
	{"Health", cat->getHealth()},
	{"Coin", cat->getCoin()},
	{"PosX", cat->getTX()},
	{"PosY", cat->getTY()},
	};
	for (Item* i : cat->getInventory()->getItems()) {
		if (i != NULL) gameData.insert({ i->getName(), i->getQuantity() });
	}

	SaveManager::GetInstance()->saveGame("savegame.txt", gameData);
	std::cout << "Game close" << std::endl;

	delete shop;
	shop = nullptr;

	return true;
}

void Play::update()
{
	Input::GetInstance()->setCurrentWindow("play");

	cam = Camera::GetInstance()->getPosition();
	float dt = Timer::GetInstance()->getDeltaTime();

	cat->update(dt);

	if (cat->getIs_Shopping() && !shop->get_IsVisible()) {
		shop->toggleShopUI();
	}
	else if (!cat->getIs_Shopping() && shop->get_IsVisible()) {
		shop->toggleShopUI();
	}

	shop->update(cam.X, cam.Y);
	Camera::GetInstance()->update(dt);
}

void Play::render()
{

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
	}
	else {
		TextureManager::GetInstance()->draw("shopkeeper", 445, 520, 36, 36);
		m_Tile->render("Shopkeeper");
	}

	if (shop != NULL && shop->get_IsVisible()) {
		shop->render(Engine::GetInstance()->GetRenderer());
	}

	cat->drawInv();

	cam = Camera::GetInstance()->getPosition();
	TextureManager::GetInstance()->draw("pause_button", cam.X + 700, cam.Y, 32, 32, SDL_FLIP_NONE, 2);
	//Input::GetInstance()->renderButtons(Engine::GetInstance()->GetRenderer());
}

void Play::initButton()
{
	Input::GetInstance()->addButton(cam.X + 705, cam.Y + 10, 54, 40, "play", [this]() {
		std::cout << "Pause" << std::endl;
		}, []() { std::cout << "Button hovered\n"; });
}

void Play::openMenu()
{
}

void Play::pauseGame()
{
}
