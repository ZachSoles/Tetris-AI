#include "game.h"
#include "sdlHandler.h"
#include <string>
#include <iostream>  // For error output
#include <chrono>    // For timing
#include <thread>   // Required for std::this_thread::sleep_for


int main(int argc, char* argv[]) {
    // Initalize Game and SDL handler
    SDLHandler sdl = SDLHandler("Tetris", GRID_WIDTH, GRID_HEIGHT);
    sdl.createWindow();
    Game tetrisGame = Game();

    // Main Game Loop
    bool running = true;
    std::cout << "Starting game..."  << std::endl;
    std::vector<coord> coordinates = tetrisGame.getCurrentBlockPosition();
    double frameTime = 1.0 / 5.0; // Target frame time (60 Hz)
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // Draw initial block
    sdl.clearRenderer();
    coordinates = tetrisGame.getCurrentBlockPosition();
    for (int i = 0; i < coordinates.size(); i++) {
        sdl.drawSprite(coordinates[i].x, coordinates[i].y, SDL_COLOR::BLUE);
    }
    sdl.updateRenderer();

    while (running) {
        // Run a single round of tetris
        tetrisGame.executeGame();
        // Get user input
        sdl.pollInput();

        // Pause and turn off game if quitting has been requested
        if (sdl.getQuitRequested()) {
            running = false;
            sdl.close();
        }

        keyMap key_pressed = sdl.getLastKeyPressed();

        switch (key_pressed) {
            case keyMap::LEFT:
                tetrisGame.moveLeft();
                break;
            case keyMap::RIGHT:
                tetrisGame.moveRight();
                break;
            case keyMap::DOWN:
                tetrisGame.moveDown();
                break;
            case keyMap::ROTATE:
                tetrisGame.rotate();
                break;
            case keyMap::PAUSE:
                // Unpause game if already paused, else pause the current game
                if (tetrisGame.isPaused()) {
                    tetrisGame.unPauseGame();
                } else {
                    tetrisGame.pauseGame();
                }
            default:
                break;
        }

        if (tetrisGame.shouldRedraw()) {
            sdl.clearRenderer();
            // Draw the current block on the grid
            coordinates = tetrisGame.getCurrentBlockPosition();
            for (int i = 0; i < coordinates.size(); i++) {
                sdl.drawSprite(coordinates[i].x, coordinates[i].y, SDL_COLOR::BLUE);
            }

            // Draw the rest of the grid
            for (int y = 0; y < GRID_HEIGHT; y++) {
                for (int x = 0; x < GRID_WIDTH; x++) {
                    if (tetrisGame.blockExists(x, y)) {
                        sdl.drawSprite(x, y, SDL_COLOR::BLUE);
                    }
                }
            }
            sdl.updateRenderer();
            tetrisGame.resetRedrawFlag();
        }

        // Calculate elapsed time and sleep if necessary
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = t2 - t1;
        if (elapsed.count() < frameTime) {
            std::this_thread::sleep_for(std::chrono::duration<double>(frameTime - elapsed.count()));
        }

        // Update the time point for the next iteration
        t1 = t2;
    }
    sdl.close();
    return 0;
}
