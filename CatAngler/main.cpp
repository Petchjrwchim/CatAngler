//#include <iostream>
//#include "SDL.h"
//#include "Engine.h"
//#include "Timer.h"
//
//using namespace std;
//
//int main(int argc, char* args[]) {
//
//	Engine::GetInstance()->init();
//
//	while (Engine::GetInstance()->IsRunning()) {
//		Engine::GetInstance()->event();
//		Engine::GetInstance()->update();
//		Engine::GetInstance()->render();
//		Timer::GetInstance()->Tick();
//
//	}
//
//	Engine::GetInstance()->clean();
//	return 0;
//}
#include <SDL.h>
#include <SDL_image.h>
#include "tinyxml.h"
#include <iostream>
#include <string>
#include <vector>

// Define the screen dimension constants
const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 680;

// Tile texture
struct TileTexture {
    SDL_Texture* texture;
    int width, height;
};

// Initialize SDL and global variables
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("TMX Map Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(std::string path) {
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

// Function to load the TMX file and textures
bool loadMedia(TileTexture& tileTexture, const std::string& tmxFilePath) {
    // Load TMX file
    TiXmlDocument doc(tmxFilePath.c_str());
    if (!doc.LoadFile()) {
        std::cout << "Could not load TMX file!" << std::endl;
        return false;
    }

    // Assume a single tileset for simplicity
    TiXmlElement* tilesetElement = doc.FirstChildElement("map")->FirstChildElement("tileset");
    std::string imageSource = tilesetElement->FirstChildElement("image")->Attribute("source");

    // Load texture
    tileTexture.texture = loadTexture(imageSource);
    if (tileTexture.texture == nullptr) {
        std::cout << "Failed to load tileset texture!" << std::endl;
        return false;
    }

    // Assume each tile is 32x32 for simplicity
    tileTexture.width = 16;
    tileTexture.height = 16;

    return true;
}

// Function to render the map
void renderMap(TileTexture& tileTexture) {
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Assuming the map is 30 tiles wide and 20 tiles high
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 30; ++x) {
            SDL_Rect srcRect = { 0, 0, tileTexture.width, tileTexture.height }; // Assuming the tile you want to draw is the first one
            SDL_Rect dstRect = { x * tileTexture.width, y * tileTexture.height, tileTexture.width, tileTexture.height };
            SDL_RenderCopy(gRenderer, tileTexture.texture, &srcRect, &dstRect);
        }
    }

    // Update screen
    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
        return -1; // Initialization failed
    }

    // Load media
    TileTexture tileTexture;
    if (!loadMedia(tileTexture, "assets/images/map.tmx")) {
        std::cout << "Failed to load media!" << std::endl;
        close(); // Ensure resources are cleaned up
        return -1;
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Render map
        renderMap(tileTexture);
    }

    // Free resources and close SDL
    close();

    return 0;
}
