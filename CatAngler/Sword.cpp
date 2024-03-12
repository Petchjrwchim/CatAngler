#include "Sword.h"
#include "CollisionHandler.h"

Sword::Sword(int quantity, const std::string& name, const std::string& type, const std::string& texture, int price, int endurance, int damage)
	: Item(quantity, name, type, texture, price)
{
	setEndurance(endurance);
	setDamage(damage);

	m_AimationS = new Animation();
	m_AimationS->setProps(getID(), 1, 4, 100);

	m_Collider = new Collider();
	m_Collider->setBuffer(5, 5, -10, -10);

}

std::string Sword::getDescription()
{
	return "Use for fighting";
}

void Sword::use()
{
	m_Collider->set(m_X, m_Y, 32, 32);

	m_AimationS->setProps(getID(), 1, 1, 100, SDL_FLIP_NONE);
	if (Input::GetInstance()->getMouseButtonDown(1)) m_AimationS->setProps(getID(), 1, 4, 100);
    if (Input::GetInstance()->getMouseButtonDownOnetime(1)) {
		m_AimationS->setProps(getID(), 1, 4, 100);
		for (Enemy* i : m_enemies) {
			if (i->getHealth() > 0) {
				if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), i->getCollider()->get())) {
					std::cout << "hit" << std::endl;
					i->reduceHealth(getDamage());
					setEndurance(getEndurance() - 2);
				}
			}
		}

    }
	if (getEndurance() <= 0) {
		removeitems(1);
	}

	m_AimationS->update();
}

void Sword::draw()
{
	if (m_Direction == 'W') {
		m_AimationS->setProps(getID(), 1, 4, 100);
		m_Y -= 10;
		m_X -= 16;
	}
	if (m_Direction == 'A') {
		m_AimationS->setProps(getID(), 1, 4, 100, SDL_FLIP_HORIZONTAL);
		m_X -= 32;
	}
	if (m_Direction == 'S') {
		m_AimationS->setProps(getID(), 1, 4, 100, SDL_FLIP_VERTICAL);
		m_Y += 10;
		m_X -= 16;
	}
	if (m_Direction == 'D') {
		m_AimationS->setProps(getID(), 1, 4, 100);
	}
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
