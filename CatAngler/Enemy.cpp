#include "Enemy.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "TextureManager.h"
#include "Camera.h"

Enemy::Enemy(Properties* props, int health) : Character(props), m_Health(health)
{
	m_Flip = SDL_FLIP_NONE;

	m_RigidBody = new RigidBody();

	m_Collider = new Collider();
	m_Collider->setBuffer(-10, -10, 20, 15);

	m_AimationE = new Animation();
	m_AimationE->setProps(m_TextureID, 1, 4, 150);

}

void Enemy::draw()
{
	m_AimationE->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	TextureManager::GetInstance()->draw("shark", m_Transform->X, m_Transform->Y, 32, 32, SDL_FLIP_HORIZONTAL);

}

void Enemy::setTarget(int x, int y, SDL_Rect target)
{
	t_X = x;
	t_Y = y;
	m_Target = target;

}

void Enemy::update(float dt)
{
	int time = 1;
	//std::cout << m_Transform->X << "," << m_Transform->Y << std::endl;
	
	if (!CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target)) {
		
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
			m_Transform->X -= 1;
		}

		m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
		if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
			m_Transform->Y -= 1;
		}
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target)) {
		m_AimationE->setProps("shark_attack", 1, 4, 150, m_Flip);
	}

	m_Origin->x = m_Transform->X + m_Width / 2;
	m_Origin->y = m_Transform->Y + m_Height / 2;
	m_AimationE->update();
}

void Enemy::clean()
{
	TextureManager::GetInstance()->clean();
}
