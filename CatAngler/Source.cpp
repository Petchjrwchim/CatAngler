//
//#include <SDL.h>
//
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <sstream>
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//
//SDL_Rect fishSpriteClips[5];
//
//struct AnimatedFish {
//    SDL_Rect rect;        // The actual position and size of the fish sprite
//    SDL_Rect hitbox;      // The hitbox for collision detection
//    SDL_Color color;      // This is not needed if you're using a sprite sheet
//    SDL_Rect spriteClip;  // The part of the sprite sheet that represents the fish
//};
//
//const int FISH_COUNT = 3;
//int screenWidth, screenHeight;
//
//
//const float fishScaleFactor = 5.0f; // Example: 2 times larger
//
//void moveFish(AnimatedFish& fish, int screenWidth, int screenHeight) {
//    // Define the movement speed
//    int moveSpeed = 20;
//
//    // Randomly change direction at random intervals
//    if (rand() % 60 == 0) { // On average, change direction every 60 frames
//        fish.rect.x += (rand() % 3 - 1) * moveSpeed; // Move left, right, or stay in the same X
//        fish.rect.y += (rand() % 3 - 1) * moveSpeed; // Move up, down, or stay in the same Y
//    }
//
//    // Keep the fish within the bounds of the screen
//    if (fish.rect.x < 0) fish.rect.x = 0;
//    //if (fish.rect.y < 0) fish.rect.y = 0;
//    if (fish.rect.x + fish.rect.w > screenWidth) fish.rect.x = screenWidth - fish.rect.w;
//    //if (fish.rect.y + fish.rect.h > screenHeight) fish.rect.y = screenHeight - fish.rect.h;
//
//    // Update the hitbox position to follow the fish
//    int hitboxPadding = 10;
//    fish.hitbox.x = fish.rect.x + hitboxPadding;
//    fish.hitbox.y = fish.rect.y + hitboxPadding;
//    fish.hitbox.w = fish.rect.w - 2 * hitboxPadding;
//    fish.hitbox.h = fish.rect.h - 2 * hitboxPadding;
//}
//
//void spawnFish(AnimatedFish& fish, int screenWidth, int screenHeight) {
//    // Set the size of the fish sprite
//    fish.rect.w = static_cast<int>(fishSpriteClips[0].w * fishScaleFactor);
//    fish.rect.h = static_cast<int>(fishSpriteClips[0].h * fishScaleFactor);
//
//    // Set the position of the fish sprite
//    fish.rect.x = rand() % (screenWidth - fish.rect.w);
//    fish.rect.y = screenHeight - 100;
//
//    // Set the hitbox relative to the rect
//    // This example assumes you want the hitbox to be centrally located within the rect and smaller
//    int hitboxPadding = 10; // Adjust the padding based on your game's needs
//    fish.hitbox.x = fish.rect.x + hitboxPadding;
//    
//    fish.hitbox.w = fish.rect.w - 2 * hitboxPadding;
//    fish.hitbox.h = fish.rect.h - 2 * hitboxPadding;
//
//    // Choose a random sprite for the fish
//    fish.spriteClip = fishSpriteClips[rand() % 5];
//}
//
//
//enum GameState {
//    BOATING,
//    FISHING
//};
//
//void drawFishIcon(SDL_Renderer* renderer, int x, int y) {
//    SDL_Rect fishIcon = { x, y, 20, 10 }; // Small rectangle as fish icon
//    SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x80, 0xFF); // Color for fish icon
//    SDL_RenderFillRect(renderer, &fishIcon);
//}
//
//bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
//    return (a.x < b.x + b.w) &&
//        (a.x + a.w > b.x) &&
//        (a.y < b.y + b.h) &&
//        (a.y + a.h > b.y);
//}
//
//int main(int argc, char* args[]) {
//
//    bool isMoving = false;
//    srand(time(NULL));
//    GameState currentState = BOATING;
//    int fishCaught = 0;
//
//    // Initialize SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    // Initialize SDL_ttf
//    if (TTF_Init() == -1) {
//        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
//        // Handle error...
//    }
//
//    TTF_Font* font = TTF_OpenFont("assets\\fonts\\PixelifySans.ttf", 28); // Replace with the path to your font file and desired font size
//    if (font == NULL) {
//        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
//        // Handle error...
//    }
//
//    SDL_DisplayMode current;
//    int displayIndex = 0; // Default to the first display
//    if (SDL_GetCurrentDisplayMode(displayIndex, &current) != 0) {
//        SDL_Log("Could not get display mode for video display #%d: %s", displayIndex, SDL_GetError());
//        return 1;
//    }
//
//    int screenWidth = 800;
//    int screenHeight = 600;
//
//    SDL_Window* window = SDL_CreateWindow("SDL2 Basic Game",
//    SDL_WINDOWPOS_UNDEFINED,
//    SDL_WINDOWPOS_UNDEFINED,
//    screenWidth,
//    screenHeight,
//    SDL_WINDOW_SHOWN);
//
//    if (window == NULL) {
//        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//
//    // Create renderer
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (renderer == NULL) {
//        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//    SDL_Texture* fishSpriteSheet = IMG_LoadTexture(renderer, "assets\\images\\Sprite-fish.png");
//    if (!fishSpriteSheet) {
//        std::cerr << "Failed to load fish sprite sheet: " << IMG_GetError() << std::endl;
//        // Handle error...
//    }
//
//    for (int i = 0; i < 5; ++i) {
//        fishSpriteClips[i].x = 0; // Replace with your fish sprite's width
//        fishSpriteClips[i].y = i * 32;
//        fishSpriteClips[i].w = 64; // Replace with your fish sprite's width
//        fishSpriteClips[i].h = 32; // Replace with your fish sprite's height
//    }
//
//    SDL_Texture* spriteSheetTexture = IMG_LoadTexture(renderer, "assets\\images\\Sprite-0004.png");
//    if (!spriteSheetTexture) {
//        std::cerr << "Failed to load sprite sheet: " << IMG_GetError() << std::endl;
//        // Handle error
//    }
//
//    SDL_Texture* hookTexture = IMG_LoadTexture(renderer, "assets\\images\\Sprite-0003.png");
//    // Check if the hook texture loaded successfully
//    if (!hookTexture) {
//        std::cerr << "Failed to load hook texture: " << IMG_GetError() << std::endl;
//        // Handle error...
//    }
//
//    // Get the original size of the hook texture
//    SDL_Rect hookSrc;
//    SDL_QueryTexture(hookTexture, NULL, NULL, &hookSrc.w, &hookSrc.h);
//
//    // Set the scaled size of the hook
//    SDL_Rect hookDst;
//    // Adjust the scaling factor to match the size of the old hook sprite
//    float hookScaleFactor = 5.0f; // This is an example, adjust as necessary
//    hookDst.w = static_cast<int>(hookSrc.w * hookScaleFactor);
//    hookDst.h = static_cast<int>(hookSrc.h * hookScaleFactor);
//
//    const int HOOK_ANIMATION_FRAMES = 8; // Number of frames in the hook animation
//    SDL_Rect hookClips[HOOK_ANIMATION_FRAMES];
//    for (int i = 0; i < HOOK_ANIMATION_FRAMES; ++i) {
//        hookClips[i].x = i * 64; // Replace 64 with the width of one frame
//        hookClips[i].y = 0;
//        hookClips[i].w = 64; // Replace 64 with the width of one frame
//        hookClips[i].h = 64; // Replace 64 with the height of one frame
//    }
//
//    int currentHookFrame = 0;
//    float hookTimer = 0.0f;
//    const float hookFrameChangeTime = 0.1f;
//
//    SDL_Texture* rodTexture = IMG_LoadTexture(renderer, "assets\\images\\Sprite-0002.png");
//    // Check if the rod texture loaded successfully
//    if (!rodTexture) {
//        std::cerr << "Failed to load rod animation texture: " << IMG_GetError() << std::endl;
//        // Handle error...
//    }
//
//    SDL_Rect rodClips[21];
//    for (int i = 0; i < 21; ++i) {
//        rodClips[i].x = i * 64;
//        rodClips[i].y = 0;
//        rodClips[i].w = 64;
//        rodClips[i].h = 64;
//    }
//
//    float floorScaleFactor = 5.0f; // Adjust this value as needed to match the cat's scale
//
//    SDL_Texture* floorTexture = IMG_LoadTexture(renderer, "assets\\images\\Sprite-0001.png");
//    if (!floorTexture) {
//        std::cerr << "Failed to load floor texture: " << IMG_GetError() << std::endl;
//        // Handle error...
//        SDL_Quit();
//        return 1;
//    }
//
//    // Get the original size of the floor texture
//    SDL_Rect floorTileSrc;
//    SDL_QueryTexture(floorTexture, NULL, NULL, &floorTileSrc.w, &floorTileSrc.h);
//
//    // Set the scaled size of the floor tile
//    SDL_Rect floorTileDst;
//    floorTileDst.w = static_cast<int>(floorTileSrc.w * floorScaleFactor);
//    floorTileDst.h = static_cast<int>(floorTileSrc.h * floorScaleFactor);
//
//    // Calculate the number of tiles needed to cover the screen width
//    int tilesCount = screenWidth / floorTileDst.w + 1; // +1 to cover any gaps
//
//    // Define the clips for walking animation frames
//    SDL_Rect spriteClips[6];
//    for (int i = 0; i < 6; ++i) {
//        spriteClips[i].x = i * 64; // Replace with the width of one frame
//        spriteClips[i].y = 0;
//        spriteClips[i].w = 64; // Replace with the width of one frame
//        spriteClips[i].h = 64; // Replace with the height of one frame
//    }
//
//
//
//    int currentFrame = 0;
//    int frameCount = 6;
//
//    float timer = 0.0f; // Timer to track animataion progress
//
//    bool quit = false;
//    SDL_Event e;
//    SDL_Rect boat = { screenWidth / 2 - 50, screenHeight - 700, 100, 50 };
//    SDL_Rect hook = { screenWidth / 2, screenHeight / 2 - 10, 20, 20 };  // Position hook
//    int hookSpeed = 5;
//    AnimatedFish fish[FISH_COUNT];
//
//    // Initialize fish for fishing state
//    for (int i = 0; i < FISH_COUNT; ++i) {
//        fish[i].rect.w = 30;
//        fish[i].rect.h = 20;
//        spawnFish(fish[i], screenWidth, screenHeight);
//    }
//
//    Uint32 lastFrameTicks = SDL_GetTicks();
//    float deltaTime = 0.0f;
//
//    float scaleFactor = 5.0f;
//    SDL_RendererFlip flipType = SDL_FLIP_NONE; // Used to determine sprite flipping
//
//    const int FPS = 60;
//    const int frameDelay = 1000 / FPS;
//    Uint32 frameStart;
//    int frameTime;
//
//    int rodAnimationFrame = 0;
//    int rodAnimationFrames = 21;
//    float rodAnimationTimer = 0.0f;
//    const float rodFrameChangeTime = 0.1f;
//    bool isRodAnimationPlaying = false;
//
//
//    bool isFullscreen = false;
//
//    const float frameChangeTime = 0.1f; // Time in seconds for changing frames
//    float animationTimer = 0.0f;
//
//    while (!quit) {
//        frameStart = SDL_GetTicks();
//        deltaTime = (SDL_GetTicks() - lastFrameTicks) / 1000.0f;  // Calculate deltaTime
//
//        while (SDL_PollEvent(&e) != 0) {
//            // Check for quit event
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//            // Handle fullscreen toggle
//            else if (e.type == SDL_KEYDOWN) {
//                if (e.key.keysym.sym == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
//                    isFullscreen = !isFullscreen;  // Toggle the state
//                    SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
//                }
//            }
//        }
//        
//        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
//        isMoving = false; // Reset the isMoving flag
//        if (currentState == BOATING) {
//            if (currentKeyStates[SDL_SCANCODE_LEFT]) {
//                boat.x -= hookSpeed;
//                flipType = SDL_FLIP_HORIZONTAL;
//                isMoving = true;
//            }
//            if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
//                boat.x += hookSpeed;
//                flipType = SDL_FLIP_NONE;
//                isMoving = true;
//            }
//            if (currentKeyStates[SDL_SCANCODE_F]) {
//                isRodAnimationPlaying = true;
//                rodAnimationFrame = 0;
//            }
//        }
//        else if (currentState == FISHING) {
//            if (currentKeyStates[SDL_SCANCODE_LEFT]) {
//                hook.x -= hookSpeed;
//            }
//            if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
//                hook.x += hookSpeed;
//            }
//        }
//
//        if (currentState == BOATING && isMoving) {
//            animationTimer += deltaTime;
//            if (animationTimer >= frameChangeTime) {
//                currentFrame = (currentFrame + 1) % frameCount;
//                animationTimer = 0.0f;
//            }
//        }
//        else {
//            currentFrame = 0;
//        }
//
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        // Render the boat using the sprite
//        if (currentState == BOATING) {
//
//            SDL_Rect& catClip = spriteClips[currentFrame]; // Renamed from currentClip to catClip
//            SDL_Rect catRenderQuad = { // Renamed from renderQuad to catRenderQuad
//                boat.x,
//                boat.y - 5,
//                static_cast<int>(catClip.w * scaleFactor), // Scaled width
//                static_cast<int>(catClip.h * scaleFactor)  // Scaled height
//            };
//            SDL_RenderCopyEx(renderer, spriteSheetTexture, &catClip, &catRenderQuad, 0, NULL, flipType);
//
//            for (int i = 0; i < tilesCount; ++i) {
//                floorTileDst.x = i * floorTileDst.w;
//                floorTileDst.y = screenHeight - floorTileDst.h - 300; // Position at the bottom of the screen
//                SDL_RenderCopy(renderer, floorTexture, NULL, &floorTileDst);
//            }
//
//            // Draw the fish caught icons and text
//            for (int i = 0; i < fishCaught; ++i) {
//                drawFishIcon(renderer, screenWidth - 30 - i * 25, 10);
//            }
//
//            SDL_Color textColor = { 0, 0, 0, 255 }; // Black color
//            std::stringstream ss;
//            ss << "Fish Caught: " << fishCaught;
//            std::string fishCountText = ss.str();
//
//            SDL_Surface* textSurface = TTF_RenderText_Solid(font, fishCountText.c_str(), textColor);
//
//            // Check if the text surface is created successfully
//            if (textSurface == nullptr) {
//                std::cerr << "Unable to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
//            }
//            else {
//                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//                int textWidth = textSurface->w;
//                int textHeight = textSurface->h;
//                SDL_FreeSurface(textSurface);
//                SDL_Rect renderQuad = { screenWidth - textWidth - 10, 10, textWidth, textHeight };
//                SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
//                SDL_DestroyTexture(textTexture);
//            }
//
//            if (isRodAnimationPlaying) {
//                rodAnimationTimer += deltaTime;
//                if (rodAnimationTimer >= rodFrameChangeTime) {
//                    rodAnimationFrame++;
//                    rodAnimationTimer = 0.0f;
//
//                    // If the last frame of the rod animation has played, stop the animation
//                    if (rodAnimationFrame >= rodAnimationFrames) {
//                        isRodAnimationPlaying = false;
//                        rodAnimationFrame = 0;
//                        // Transition to FISHING state or any other state as necessary
//                        currentState = FISHING;
//                    }
//                }
//
//                // Draw the rod animation over the existing screen contents
//                SDL_Rect& currentClip = rodClips[rodAnimationFrame];
//                SDL_Rect renderQuad = {
//                    // Position next to the cat, adjust x and y as necessary
//                    (flipType == SDL_FLIP_NONE) ? boat.x + 50 : boat.x - 50,
//                    boat.y,
//                    static_cast<int>(catClip.w* scaleFactor), // Scaled width
//                    static_cast<int>(catClip.h* scaleFactor)  // Scaled height
//                };
//
//                SDL_RenderCopyEx(renderer, rodTexture, &currentClip, &renderQuad, 0, NULL, flipType);
//            }
//            else {
//
//                int offset = 0;
//                if (currentFrame > 3) {
//                    offset = 5;
//                }
//                else {
//                    offset = 0;
//                }
//
//                SDL_Rect& currentClip = rodClips[0];
//                SDL_Rect renderQuad = {
//                    // Position next to the cat, adjust x and y as necessary
//                    (flipType == SDL_FLIP_NONE) ? boat.x + 50 - offset : boat.x - 50 + offset,
//                    boat.y,
//                    static_cast<int>(catClip.w * scaleFactor), // Scaled width
//                    static_cast<int>(catClip.h * scaleFactor)  // Scaled height
//                };
//
//                SDL_RenderCopyEx(renderer, rodTexture, &currentClip, &renderQuad, 0, NULL, flipType);
//            }
//        }
//        else if (currentState == FISHING) {
//            // Move fish upwards
//
//            hookTimer += deltaTime;
//            if (hookTimer >= hookFrameChangeTime) {
//                currentHookFrame = (currentHookFrame + 1) % HOOK_ANIMATION_FRAMES;
//                hookTimer = 0.0f;
//            }
//
//            // Set the position of the hook sprite
//            hookDst.x = hook.x;
//            hookDst.y = hook.y;
//
//            SDL_Rect& hookClip = hookClips[currentHookFrame];
//            hookDst.w = static_cast<int>(hookClip.w * scaleFactor); // Scaled width
//            hookDst.h = static_cast<int>(hookClip.h * scaleFactor); // Scaled height
//
//            SDL_RenderCopy(renderer, hookTexture, &hookClip, &hookDst);
//
//            int shrinkAmount = 100; // This is an arbitrary number; adjust as needed for your sprite
//
//            // Calculate the smaller hitbox within hookDst
//            SDL_Rect hookHitbox;
//            hookHitbox.x = hookDst.x + shrinkAmount;
//            hookHitbox.y = hookDst.y + shrinkAmount;
//            hookHitbox.w = hookDst.w - 2 * shrinkAmount; // Shrink on both left and right sides
//            hookHitbox.h = hookDst.h - 2 * shrinkAmount;
//
//            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red color
//            SDL_RenderDrawRect(renderer, &hookHitbox);
//
//            for (int i = 0; i < FISH_COUNT; ++i) {
//                fish[i].rect.y -= 5; // Move the fish upwards
//                if (fish[i].rect.y + fish[i].rect.h < 0) {
//                    spawnFish(fish[i], screenWidth, screenHeight);
//                }
//
//                if (checkCollision(hookHitbox, fish[i].hitbox)) {
//                    spawnFish(fish[i], screenWidth, screenHeight);
//                    fishCaught++;
//                    currentState = BOATING; // Switch back to boating
//                }
//                fish[i].hitbox.y = fish[i].rect.y + 10;
//                moveFish(fish[i], screenWidth, screenHeight);
//                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red color for the hitbox
//                SDL_RenderDrawRect(renderer, &fish[i].hitbox);
//
//                SDL_Rect renderQuad = {
//                    fish[i].rect.x, fish[i].rect.y,
//                    static_cast<int>(fish[i].spriteClip.w * fishScaleFactor),
//                    static_cast<int>(fish[i].spriteClip.h * fishScaleFactor)
//                };
//                SDL_RenderCopy(renderer, fishSpriteSheet, &fish[i].spriteClip, &fish[i].rect);
//
//                // Optionally draw the hitbox for debugging
//
//            }
//        }
//
//        // Update screen
//        SDL_RenderPresent(renderer);
//
//        lastFrameTicks = frameStart;  // Update lastFrameTicks for next deltaTime calculation
//        frameTime = SDL_GetTicks() - frameStart;
//        if (frameDelay > frameTime) {
//            SDL_Delay(frameDelay - frameTime);
//        }
//
//    }
//
//    TTF_CloseFont(font);
//    TTF_Quit();
//
//    // Destroy window and renderer
//    SDL_DestroyTexture(fishSpriteSheet);
//    SDL_DestroyTexture(hookTexture);
//    SDL_DestroyTexture(spriteSheetTexture);
//    SDL_DestroyTexture(floorTexture);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
