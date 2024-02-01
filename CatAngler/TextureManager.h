#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include "SDL.h"
#include "SDL.h"
#include "SDL_Image.h"
#include <map>

class TextureManager
{
	public:
		static TextureManager* GetInstance() {
			return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
		}

		bool load(std::string id, std::string filename);
		void drop(std::string id);
		void clean();

		void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE);
		void drawframe(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		TextureManager(){}
		std::map<std::string, SDL_Texture*> m_TextureMap;
		static TextureManager* s_Instance;
};

#endif 