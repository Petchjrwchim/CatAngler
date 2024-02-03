#include <iostream>
#include "SDL.h"
#include "Engine.h"
#include "Timer.h"

using namespace std;

int main(int argc, char* args[]) {

	Engine::GetInstance()->init();

	while (Engine::GetInstance()->IsRunning()) {
		Engine::GetInstance()->event();
		Engine::GetInstance()->update();
		Engine::GetInstance()->render();
		Timer::GetInstance()->Tick();

	}

	Engine::GetInstance()->clean();
	return 0;
}
//#include <SDL.h>
//#include "tileson.hpp"
//#include <iostream>
//#include <filesystem>
//#include <SDL_Image.h>
//namespace fs = std::filesystem;
//
//// Function to load an SDL_Texture from a file
//SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer) {
//    SDL_Surface* surface = IMG_Load(path.c_str()); // Use IMG_Load instead of SDL_LoadBMP
//    if (!surface) {
//        std::cout << "Error loading surface: " << IMG_GetError() << std::endl; // Use IMG_GetError() to get the error message
//        return nullptr;
//    }
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//    if (!texture) {
//        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
//    }
//    return texture;
//}
//
//int main(int argc, char* argv[]) {
//    // Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//        return -1;
//    }
//
//    // Create window
//    SDL_Window* window = SDL_CreateWindow("Tileson SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//    if (!window) {
//        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    // Create renderer
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer) {
//        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    // Parse the map with Tileson
//    tson::Tileson t;
//    std::unique_ptr<tson::Map> map = t.parse(fs::path("assets/images/map.json"));
//
//    if (map->getStatus() != tson::ParseStatus::OK) {
//        std::cout << "Failed to load map!" << std::endl;
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    // Main loop flag
//    bool quit = false;
//
//    // Event handler
//    SDL_Event e;
//
//    // While application is running
//    while (!quit) {
//        // Handle events on queue
//        while (SDL_PollEvent(&e) != 0) {
//            // User requests quit
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // Clear screen
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        // Render map
//        for (auto& layer : map->getLayers()) {
//            if (layer.getType() == tson::LayerType::TileLayer) {
//                for (auto& [pos, tile] : layer.getTileData()) { // If pos is a tuple<int, int>
//                    tson::Tileset* tileset = tile->getTileset();
//                    tson::Rect drawingRect = tile->getDrawingRect();
//
//                    SDL_Rect srcRect = { drawingRect.x, drawingRect.y, drawingRect.width, drawingRect.height };
//                    tson::Vector2f tilePosition = tile->getPosition(pos); // Corrected to pass 'pos'
//                    SDL_Rect dstRect = { static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y), tile->getTileSize().x, tile->getTileSize().y };
//
//                    // Load each tileset image into an SDL_Texture
//                    SDL_Texture* texture = loadTexture(tileset->getImage().string(), renderer);
//                    if (texture) {
//                        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
//                        SDL_DestroyTexture(texture); // Free the texture after use
//                    }
//                }
//            }
//        }
//
//        // Update screen
//        SDL_RenderPresent(renderer);
//    }
//
//    // Free resources and close SDL
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
