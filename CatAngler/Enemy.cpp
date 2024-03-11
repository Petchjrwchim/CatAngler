#include "Enemy.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "TextureManager.h"
#include "Camera.h"

int h;

Enemy::Enemy(Properties* props, int health, int frame) : Character(props), m_Frame(frame)
{
	m_Flip = SDL_FLIP_NONE;

	m_RigidBody = new RigidBody();

	m_Collider = new Collider();
	if (m_TextureID == "shark") m_Collider->setBuffer(-10, -10, 20, 15);
	if (m_TextureID == "squid") m_Collider->setBuffer(-10, -20, -10, 0);
	//shark -10 -10 20 15
	//squid -10, -20, -10, 0

	m_AimationE = new Animation();
	m_AimationE->setProps(m_TextureID + "_walk", 1, m_Frame, 150);

	m_Health = health;

}

void Enemy::draw()
{	
	m_AimationE->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	h = m_Health;
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
	int IsKnockback = 1;
	if (m_Health != h) IsKnockback = -5;
	int lastX = m_Transform->X;
	int lastY = m_Transform->Y;

	if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target) && SDL_GetTicks() / 100 - attackTime > 1) {
		m_AimationE->setProps(m_TextureID + "_attack", 1, m_Frame, 100, m_Flip);
	} else {
		m_AimationE->setProps(m_TextureID + "_walk", 1, m_Frame, 150, m_Flip);
	}
	if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target) && SDL_GetTicks() / 100 - attackTime > 2) {
		*m_playerHealth -= 1;
		attackTime = SDL_GetTicks() / 100;
	}

	if (!CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target)) {
		attackTime = SDL_GetTicks() / 100;
	}
	if (!CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), m_Target)) {
		if (t_Y - m_Target.h / 2 > m_Transform->Y || t_Y > m_Transform->Y) {
			lastDirection = 'W';
			m_Transform->Y += 1 * SPEED_ENEMY * IsKnockback;
		}

		if (t_Y - m_Target.h / 2 < m_Transform->Y || t_Y < m_Transform->Y) {
			lastDirection = 'S';
			m_Transform->Y -= 1 * SPEED_ENEMY * IsKnockback;
		}

		if (t_X - m_Target.w / 2 < m_Transform->X || t_X < m_Transform->X) {
			lastDirection = 'A';
			m_Flip = SDL_FLIP_NONE;
			m_AimationE->setProps(m_TextureID + "_walk", 1, m_Frame, 150, m_Flip);
			m_Transform->X -= 1 * SPEED_ENEMY * IsKnockback;
		}

		if (t_X - m_Target.w / 2 > m_Transform->X || t_X > m_Transform->X) {
			lastDirection = 'D';
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_AimationE->setProps(m_TextureID + "_walk", 1, m_Frame, 150, m_Flip);
			m_Transform->X += 1 * SPEED_ENEMY * IsKnockback;
		}
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), "EnemyCollision")) {
		m_Transform->X = lastX;
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), "EnemyCollision")) {
		m_Transform->Y = lastY;
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);

	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get(), "Water")) {
		m_AimationE->setProps(m_TextureID + "_dive", 1, m_Frame, 150, m_Flip);
	}

	if (CollisionHandler::GetInstance()->checkCollisionVec(m_Collider, getColliderVec())) {
		m_Transform->X = lastX;
		m_Transform->Y = lastY;
	}

	m_Origin->x = m_Transform->X + m_Width / 2;
	m_Origin->y = m_Transform->Y + m_Height / 2;
	m_AimationE->update();
}

void Enemy::clean()
{
	TextureManager::GetInstance()->clean();
}