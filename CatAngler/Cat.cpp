#include "Cat.h"
#include "TextureManager.h"
#include "Input.h"
#include "SDL.h"


Cat::Cat(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();
	m_Aimation = new Animation();
	m_Aimation->setProps(m_TextureID, 0, 5, 100);
}

void Cat::draw()
{
	m_Aimation->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Cat::update(float dt)
{
	SDL_RendererFlip f = SDL_FLIP_NONE;

	m_Aimation->setProps("player", 0, 5, 100);
	m_RigidBody->unsetForce();

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
		f = SDL_FLIP_HORIZONTAL;
		m_RigidBody->applyForceX(9*BACKWARD);
		m_Aimation->setProps("player_run", 0, 5, 100, f);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
		f = SDL_FLIP_NONE;
		m_RigidBody->applyForceX(9* FORWARD);
		m_Aimation->setProps("player_run", 0, 5, 100, f);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_W)) {
		m_RigidBody->applyForceY(9 * BACKWARD);
		m_Aimation->setProps("player_run", 0, 5, 100, f);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_S)) {
		m_RigidBody->applyForceY(9 * FORWARD);
		m_Aimation->setProps("player_run", 0, 5, 100, f);
	}

	m_RigidBody->update(0.1);
	m_Transform->translateX(m_RigidBody->position().X);
	m_Transform->translateY(m_RigidBody->position().Y);

	m_Aimation->update();
}

void Cat::clean()
{
	TextureManager::GetInstance()->clean();
}
