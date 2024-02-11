#include "TextManager.h"
#include "Engine.h"
#include <iostream>

TextManager* TextManager::s_Instance = nullptr;


bool TextManager::loadMedia(const char* fontPath, int fontSize)
{
    //font = TTF_OpenFont(fontPath, fontSize);
    //if (font == nullptr)
    //{
    //    std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    //    return false;
    //}

    return true;
}

void TextManager::clean()
{
	//std::map<std::string, SDL_Texture*>::iterator it;
	//for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
	//	SDL_DestroyTexture(it->second);

	//m_TextureMap.clear();

	//SDL_Log("Texture map cleaned");
}

void TextManager::renderText(const char* text, int x, int y, const char* fontPath, int fontSize, SDL_Color color )
{
    TTF_Font* tempFont = TTF_OpenFont(fontPath, fontSize);
    if (tempFont == nullptr)
    {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(tempFont, text, color);
    if (textSurface == nullptr)
    {
        TTF_CloseFont(tempFont);
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), textSurface);
    if (textTexture == nullptr)
    {
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(tempFont);
        std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    Vector2D cam = Camera::GetInstance()->getPosition();

    SDL_Rect renderQuad = { x - cam.X, y - cam.Y, textSurface->w, textSurface->h };
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), textTexture, nullptr, &renderQuad);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(tempFont); // Close the font after using it
}
