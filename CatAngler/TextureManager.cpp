#include "TextureManager.h"
#include "Engine.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::load(std::string id, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) {
		SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("Failed to texture from surface: %s", SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;
	return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drawframe(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { width*frame, height*row, width, height };
	SDL_Rect dstRect = { x, y, width * SCREEN_WIDTH * 0.005, height * SCREEN_WIDTH * 0.005 };

	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drop(std::string id)
{
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void TextureManager::clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	m_TextureMap.clear();

	SDL_Log("Texture map cleaned");
}


