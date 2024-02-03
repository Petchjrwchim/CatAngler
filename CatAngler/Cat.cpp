#include "Cat.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "SDL.h"


Cat::Cat(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();

	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);

	m_Aimation = new Animation();
	m_Aimation->setProps(m_TextureID, 1, 5, 100);

}

void Cat::draw()
{
	m_Aimation->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	
	Vector2D cam = Camera::GetInstance()->getPosition();
	SDL_Rect box = m_Collider->get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Cat::update(float dt)
{
	SDL_RendererFlip f = SDL_FLIP_NONE;

	m_Aimation->setProps("cat_idle", 1, 5, 100);
	m_RigidBody->unsetForce();

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
		f = SDL_FLIP_HORIZONTAL;
		m_RigidBody->applyForceX(50 * BACKWARD);
		m_Aimation->setProps("cat_walk", 1, 5, 100, f);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
		f = SDL_FLIP_NONE;
		m_RigidBody->applyForceX(50 * FORWARD);
		m_Aimation->setProps("cat_walk", 1, 5, 100, f);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_W)) {
		m_RigidBody->applyForceY(50 * BACKWARD);
		m_Aimation->setProps("cat_walk", 1, 5, 100, f);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_S)) {
		m_RigidBody->applyForceY(50 * FORWARD);
		m_Aimation->setProps("cat_walkf", 1, 5, 100, f);
	}


	m_RigidBody->update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->position().X;
	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
		//std::cout << "crash" << std::endl;
		m_Transform->X = m_LastSafePosition.X;
	}
		
	m_RigidBody->update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->position().Y;
	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
		std::cout << "crash" << std::endl;
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Origin->x = m_Transform->X + m_Width / 2;
	m_Origin->y = m_Transform->Y + m_Height / 2;
	m_Aimation->update();
}

void Cat::clean()
{
	TextureManager::GetInstance()->clean();
}
