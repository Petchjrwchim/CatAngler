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
	m_Aimation->setProps("player", 0, 5, 100);
	m_RigidBody->unsetForce();

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_A)) {
		m_RigidBody->applyForceX(2*BACKWARD);
		m_Aimation->setProps("player_run", 0, 5, 150, SDL_FLIP_HORIZONTAL);
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_D)) {
		m_RigidBody->applyForceX(2* FORWARD);
		m_Aimation->setProps("player_run", 0, 5, 150);
	}

	m_RigidBody->update(0.1);
	m_Transform->translateX(m_RigidBody->position().X);
	//m_Transform->translateY(m_RigidBody->position().Y);

	m_Aimation->update();
}

void Cat::clean()
{
	TextureManager::GetInstance()->clean();
}
