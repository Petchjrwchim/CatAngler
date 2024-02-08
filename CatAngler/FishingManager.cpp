#include "FishingManager.h"
#include "Input.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "SDL.h"
#include <iostream>

FishingManager* FishingManager::s_Instance = nullptr;

FishingManager::FishingManager(std::vector<Fish*> fishInArea)
	: fishInArea(fishInArea) 
{
	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);
}

void FishingManager::checkFishingPosition(int  x, int y, std::string map)
{
	m_Collider->set(x, y, 32, 32);

	Vector2D cam = Camera::GetInstance()->getPosition();
	SDL_Rect box = m_Collider->get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), map)) {
		std::cout << "got fish" << std::endl;
	}
}

void FishingManager::update(bool input, int x, int y)
{

}
