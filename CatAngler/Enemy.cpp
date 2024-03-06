#include "Enemy.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "TextureManager.h"
#include "Camera.h"

Enemy::Enemy(Properties* props, int health) : Character(props)
{
	m_Flip = SDL_FLIP_NONE;

	m_RigidBody = new RigidBody();

	m_Collider = new Collider();
	m_Collider->setBuffer(-10, -10, 20, 15);

	m_AimationE = new Animation();
	m_AimationE->setProps(m_TextureID, 1, 4, 150);

	m_Health = health;

}

void Enemy::draw()
{
	m_AimationE->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	TextureManager::GetInstance()->draw("shark", m_Transform->X, m_Transform->Y, 32, 32, SDL_FLIP_HORIZONTAL);

}

void Enemy::setTarget(int x, int y, int* health, SDL_Rect target)
{
	t_X = x;
	t_Y = y;
	m_playerHealth = health;
	m_Target = target;

}

void Enemy::update(float dt)
{
	if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target) && SDL_GetTicks() / 1000 - attackTime > 1) {
		m_AimationE->setProps("shark_attack", 1, 4, 150, m_Flip);
		std::cout << "got attack" << std::endl;
	} else {
		m_AimationE->setProps(m_TextureID, 1, 4, 150, m_Flip);
	}
	if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target) && SDL_GetTicks() / 1000 - attackTime > 1.75) {
		*m_playerHealth -= 1;
		attackTime = SDL_GetTicks() / 1000;
	}


	if (!CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target)) {
		attackTime = SDL_GetTicks() / 1000;
		if (t_Y > m_Transform->Y) {
			lastDirection = 'W';
			m_Transform->Y += 1 * SPEED;
		}

		if (t_Y < m_Transform->Y) {
			lastDirection = 'S';
			m_Transform->Y -= 1 * SPEED;
		}

		if (t_X < m_Transform->X) {
			lastDirection = 'A';
			m_Flip = SDL_FLIP_NONE;
			m_AimationE->setProps(m_TextureID, 1, 4, 150, m_Flip);
			m_Transform->X -= 1 * SPEED;
		}

		if (t_X > m_Transform->X) {
			lastDirection = 'D';
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_AimationE->setProps(m_TextureID, 1, 4, 150, m_Flip);
			m_Transform->X += 1 * SPEED;
		}

		m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
		if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
			m_Transform->X -= 1 * SPEED;
		}

		m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
		if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
			m_Transform->Y -= 1 * SPEED;
		}
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);

	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), "Water")) {
		m_AimationE->setProps("shark_dive", 1, 4, 150, m_Flip);
	}

	if (CollisionHandler::GetInstance()->checkCollisionVec(m_Collider, getColliderVec())) {
		m_Transform->X -= 1.2 * SPEED;
		m_Transform->Y -= 1.2 * SPEED;
	}

	m_Origin->x = m_Transform->X + m_Width / 2;
	m_Origin->y = m_Transform->Y + m_Height / 2;
	m_AimationE->update();
}

void Enemy::clean()
{
	TextureManager::GetInstance()->clean();
}