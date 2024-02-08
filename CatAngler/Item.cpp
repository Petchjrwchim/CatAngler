#include "Item.h"
#include "TextureManager.h" 


Item::Item(int id, const std::string& name, const std::string& type, const std::string& texture): m_TextureID(texture)
{

}

void Item::use(char direction, int x, int y)
{
}

std::string Item::getDescription() const
{
    return std::string();
}

void Item::draw(char direction, int x, int y) {
    
}

void Item::update(float dt) {
   
}

void Item::clean() {
    
}
