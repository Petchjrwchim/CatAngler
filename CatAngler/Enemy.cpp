#include "Enemy.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "TextureManager.h"
#include "Camera.h"

Enemy::Enemy(Properties* props) : Character(props)
{
	m_Flip = SDL_FLIP_NONE;

	m_RigidBody = new RigidBody();

	m_Collider = new Collider();
	m_Collider->setBuffer(-10, -10, 20, 15);

	m_Aimation = new Animation();
	m_Aimation->setProps(m_TextureID, 1, 1, 100);

}

void Enemy::draw()
{
	m_Aimation->draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	Vector2D cam = Camera::GetInstance()->getPosition();

}

void Enemy::setTarget(int x, int y, SDL_Rect target)
{
	t_X = x;
	t_Y = y;
	target = target;

}

void Enemy::update(float dt)
{

	//std::cout << m_Transform->X << "," << m_Transform->Y << std::endl;
	
	if (t_Y > m_Transform->Y) {
		lastDirection = 'W';
		m_Transform->Y += 1;
	}
	
	if (t_Y < m_Transform->Y) {
		lastDirection = 'S';
		m_Transform->Y -= 1;
	}

	if (t_X < m_Transform->X) {
		lastDirection = 'A';
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_Transform->X -= 1;
	}

	if (t_X > m_Transform->X) {
		lastDirection = 'D';
		m_Flip = SDL_FLIP_NONE;
		m_Transform->X += 1;
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
		m_Transform->X -=1;
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->mapCollision(m_Collider->get())) {
		m_Transform->Y -= 1;
	}

	m_Collider->set(m_Transform->X, m_Transform->Y, 32, 32);
	if (CollisionHandler::GetInstance()->checkCollision(m_Collider->get(), target)) {
		health -= 1;
	}

	m_Origin->x = m_Transform->X + m_Width / 2;
	m_Origin->y = m_Transform->Y + m_Height / 2;
	m_Aimation->update();
}

void Enemy::clean()
{
	TextureManager::GetInstance()->clean();
}
