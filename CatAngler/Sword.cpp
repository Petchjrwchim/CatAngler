#include "Sword.h"
#include "CollisionHandler.h"

Sword::Sword(int quantity, const std::string& name, const std::string& type, const std::string& texture)
	: Item(quantity, name, type, texture)
{

	m_AimationS = new Animation();
	m_AimationS->setProps("sword", 1, 4, 100);

	m_Collider = new Collider();
	m_Collider->setBuffer(0, 0, 0, 0);

}

std::string Sword::getDescription()
{
	return std::string();
}

void Sword::use()
{
	m_Collider->set(m_X, m_Y, 32, 32);

	m_AimationS->setProps("sword", 1, 1, 100, SDL_FLIP_NONE);
    if (Input::GetInstance()->getMouseButtonDown(1)) {
		m_AimationS->setProps("sword", 1, 4, 100);
		for (Enemy* i : m_enemies) {
			if (i->getHealth() > 0) {
				if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), i->getCollider()->get())) {
					std::cout << "hit" << i->getHealth() << std::endl;
					i->reduceHealth(1);
				}
			}
		}

    }

	m_AimationS->update();
}

void Sword::draw()
{
	m_AimationS->draw(m_X, m_Y, 32, 32);
}


int Sword::getX()
{
	return 0;
}

int Sword::getY()
{
	return 0;
}
