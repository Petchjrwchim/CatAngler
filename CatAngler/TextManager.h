#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H


#include "Camera.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>


class TextManager
{
public:

    static TextManager* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextManager();
    }

    bool loadMedia(const char* fontPath, int fontSize);
    void clean();
    void renderText(const char* text, int x, int y, const char* fontPath, int fontSize, SDL_Color color = { 0, 0, 0 });

private:
    //std::map<std::string, SDL_Texture*> m_TextMap;
    static TextManager* s_Instance;

};

#endif