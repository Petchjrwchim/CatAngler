#include "Animation.h"
#include "TextureManager.h"

void Animation::update()
{
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::draw(float x, float y, int spriteWidth, int spriteHeight)
{
	TextureManager::GetInstance()->drawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::setProps(std::string textureID, int spriteRow, int frame, int animSpeed, SDL_RendererFlip flip)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frame;
	m_AnimSpeed = animSpeed;
	m_Flip = flip;
}
