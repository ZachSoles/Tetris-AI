#include "sdlHandler.h"
#include <iostream>  // For error output

SDLHandler::SDLHandler(const std::string& title, int width, int height) {
    screenTitle = title;
    screenHeight = height;
    screenWidth = width;
}

keyMap SDLHandler::getLastKeyPressed() { return lastkeyPressed; }
bool SDLHandler::getQuitRequested() { return quitRequested; }
int SDLHandler::getScreenHeight() { return screenHeight; }
int SDLHandler::getScreenWidth() { return screenWidth; }

void SDLHandler::createWindow() {
    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // 2. Create SDL Window and Renderer
    window = SDL_CreateWindow(
        screenTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenWidth * PIXEL_SCALE, screenHeight * PIXEL_SCALE,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        close();
    }

    // Present the rendered content to the window
    SDL_RenderPresent(renderer);
}

void SDLHandler::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLHandler::drawSprite(int x, int y, SDL_COLOR color) {
    // Clear SDL renderer to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect pixel_rect = {x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE};
    SDL_RenderFillRect(renderer, &pixel_rect);
    SDL_RenderPresent(renderer);
}

void SDLHandler::pollInput() {
    SDL_Event event;
    lastkeyPressed = keyMap::NONE;

    // Loop through all pending SDL events
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_LEFT:
                        lastkeyPressed = keyMap::LEFT;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        lastkeyPressed = keyMap::RIGHT;
                        break;
                    case SDL_SCANCODE_DOWN:
                        lastkeyPressed = keyMap::DOWN;
                        break;
                    case SDL_SCANCODE_UP:
                        lastkeyPressed = keyMap::UP;
                        break;
                    case SDL_SCANCODE_R:
                        lastkeyPressed = keyMap::ROTATE;
                        break;
                    case SDL_SCANCODE_SPACE:
                        lastkeyPressed = keyMap::SPACE;
                        break;
                    case SDL_SCANCODE_P:
                        lastkeyPressed = keyMap::PAUSE;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        quitRequested = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                lastkeyPressed = keyMap::NONE;
                break;
            default:
                break;
        }
    }
}
