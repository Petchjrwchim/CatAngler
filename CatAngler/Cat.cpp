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

	m_Inventory = new Inventory(10);
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

void Cat::drawInv() {
	Vector2D cam = Camera::GetInstance()->getPosition();
	if (m_Inventory->checkVisible()) {
		m_Inventory->render();
	}
	m_Inventory->renderInventoryBar(cam.X, cam.Y + 530);
}

void Cat::update(float dt)
{
	int frame = 5;
	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
	m_IsMoving = false;
	m_RigidBody->unsetForce();

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_W)) {
		m_IsMoving = true;
		lastDirection = 'W';
		m_RigidBody->applyForceY(SPEED * BACKWARD);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_S)) {
		m_IsMoving = true;
		lastDirection = 'S';
		m_RigidBody->applyForceY(SPEED * FORWARD);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
		m_IsMoving = true;
		lastDirection = 'A';
		m_RigidBody->applyForceX(SPEED * BACKWARD);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
		m_IsMoving = true;
		lastDirection = 'D';
		m_RigidBody->applyForceX(SPEED * FORWARD);
	}

	if (m_IsMoving) frame = 5; else frame = 1;

	if (Input::GetInstance()->getKeyDownOnetime(SDL_SCANCODE_F)) {
		if (!m_IsFishing) {
			m_IsFishing = true;
		}
		else {
			m_IsFishing = false;
		}
	}

	if (Input::GetInstance()->getKeyDownOnetime(SDL_SCANCODE_I)) {
		m_Inventory->toggleVisibility();
	}

	if (lastDirection == 'W') {
		m_Aimation->setProps("cat_walk", 1, frame, 100, m_Flip);
	}
	if (lastDirection == 'A') {
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_Aimation->setProps("cat_walk", 1, frame, 100, m_Flip);
	}
	if (lastDirection == 'S') {
		if (m_IsMoving) m_Aimation->setProps("cat_walkf", 1, 5, 100, m_Flip); else m_Aimation->setProps("cat_idle", 1, 5, 100, m_Flip);
	}
	if (lastDirection == 'D') {
		m_Flip = SDL_FLIP_NONE;
		m_Aimation->setProps("cat_walk", 1, frame, 100, m_Flip);
	}

	if (m_IsFishing) {
		m_Aimation->setProps("cat_fishing", 1, 5, 100, m_Flip);
		m_RigidBody->unsetForce();
	}

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

void Cat::equip() {
	if (!m_Inventory->getItems().empty()) {
		m_Inventory->getItems()[0]->use(getX(), getY());
	}
}

void Cat::clean()
{
	TextureManager::GetInstance()->clean();
}
