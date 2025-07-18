#include "game.h"
#include "sdlHandler.h"
#include <string>
#include <iostream>  // For error output
#include <chrono>    // For timing
#include <ratio>


int main(int argc, char* argv[]) {
    // Initalize Game and SDL handler
    SDLHandler sdl = SDLHandler("Tetris", 100, 100);
    sdl.createWindow();
    Game tetrisGame = Game();

    // Main Game Loop
    bool running = true;
    std::cout << "Starting game..."  << std::endl;
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
    }

    return 0;
}
