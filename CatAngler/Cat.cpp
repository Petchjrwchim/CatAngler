#include "Cat.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "SDL.h"


Cat::Cat(Properties* props) : Character(props)
{

	m_Flip = SDL_FLIP_NONE;

	m_RigidBody = new RigidBody();

	m_Collider = new Collider();
	m_Collider->setBuffer(-10, -10, 20, 15);
	
	m_Aimation = new Animation();
	m_Aimation->setProps(m_TextureID, 1, 5, 100);

}

int Cat::getX()
{
	Vector2D cam = Camera::GetInstance()->getPosition();
	SDL_Rect box = m_Collider->get();
	return box.x - cam.X + m_Collider->get().w/2;
}

int Cat::getY()
{
	Vector2D cam = Camera::GetInstance()->getPosition();
	SDL_Rect box = m_Collider->get();
	return box.y - cam.Y;
}

void Cat::draw()
{
	m_Aimation->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	//Vector2D cam = Camera::GetInstance()->getPosition();
	//SDL_Rect box = m_Collider->get();
	//box.x -= cam.X;
	//box.y -= cam.Y;
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Cat::update(float dt)
{
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
	
	if (!m_IsFishing) {
		m_Aimation->setProps("cat_idle", 1, 5, 100);
		m_RigidBody->unsetForce();
	} else {
		m_Aimation->setProps("cat_fishing", 1, 5, 100, m_Flip);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_W)) {
		lastDirection = 'W';
		m_RigidBody->applyForceY(SPEED * BACKWARD);
		m_Aimation->setProps("cat_walk", 1, 5, 100, m_Flip);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_S)) {
		lastDirection = 'S';
		m_RigidBody->applyForceY(SPEED * FORWARD);
		m_Aimation->setProps("cat_walkf", 1, 5, 100, m_Flip);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
		lastDirection = 'A';
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_RigidBody->applyForceX(SPEED * BACKWARD);
		m_Aimation->setProps("cat_walk", 1, 5, 100, m_Flip);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
		lastDirection = 'D';
		m_Flip = SDL_FLIP_NONE;
		m_RigidBody->applyForceX(SPEED * FORWARD);
		m_Aimation->setProps("cat_walk", 1, 5, 100, m_Flip);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_F)) {
		if (!m_IsFishing) {
			m_IsFishing = true;
		}
		else {
			m_IsFishing = false;
		}
	}

	if (m_IsFishing == true) m_RigidBody->unsetForce();

	m_RigidBody->update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->position().X;
	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
		
	m_RigidBody->update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->position().Y;
	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
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
