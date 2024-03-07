#include "Food.h"
#include "Input.h"

Food::Food(int quantity, const std::string& name, const std::string& type, const std::string& texture, int price, int heal)
    : Item(quantity, name, type, texture, price), m_Heal(heal)
{

}

std::string Food::getDescription()
{
	return std::string();
}

void Food::use()
{
    if (Input::GetInstance()->getKeyDownOnetime(SDL_SCANCODE_E)) {
        std::cout << "Eat" << std::endl;
        *m_PlayerHealth += m_Heal;
    }
}

void Food::draw()
{
    if (m_Direction == 'W') {
        TextureManager::GetInstance()->draw(getID(), m_X - 15, m_Y - 3, 32, 10);
    }
    if (m_Direction == 'A') {
        TextureManager::GetInstance()->draw(getID(), m_X - 27, m_Y, 32, 32, SDL_FLIP_HORIZONTAL);
    }
    if (m_Direction == 'S') {
        TextureManager::GetInstance()->draw(getID(), m_X - 15, m_Y, 32, 32);
    }
    if (m_Direction == 'D') {
        TextureManager::GetInstance()->draw(getID(), m_X - 5, m_Y, 32, 32);
    }
}


