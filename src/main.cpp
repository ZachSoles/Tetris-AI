#include "game.h"

#include <SDL.h>     // Include SDL header
#include <iostream>  // For error output
#include <chrono>    // For timing
#include <vector>    // For loading ROM

// Define emulator constants (should ideally be in a common header or here)
const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;
const int PIXEL_SCALE = 10; // How much to scale each Chip-8 pixel on screen

int main(int argc, char* argv[]) {

    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. Create SDL Window and Renderer
    SDL_Window* window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * PIXEL_SCALE, CHIP8_HEIGHT * PIXEL_SCALE,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 3. Initialize Chip-8 components
    game main_game;

    // Seed random number generator once at the start for the CPU's rand()
    srand(static_cast<unsigned int>(time(nullptr)));

    // 5. Main Emulation Loop Setup
    bool running = true;
    const int CPU_CYCLES_PER_SECOND = 600; // Typically around 500-700 Hz for Chip-8
    const int TIMER_HZ = 60; // Timers decrement at 60Hz

    // Calculate duration for one CPU cycle
    const std::chrono::nanoseconds cycle_duration(1000000000 / CPU_CYCLES_PER_SECOND);
    auto last_cycle_time = std::chrono::high_resolution_clock::now();

    // To handle 60Hz timer updates
    auto last_timer_update_time = std::chrono::high_resolution_clock::now();
    const std::chrono::nanoseconds timer_update_duration(1000000000 / TIMER_HZ);

    // 6. Emulation Loop
    std::cout << "Starting emulation..."  << std::endl;
    while (running) {
        // Process SDL Events through the Input class
        input.poll_events();

        // Check for quit request from Input class
        if (input.should_quit()) {
            running = false;
            break;
        }

        // Emulate CPU cycles based on target speed
        auto current_time = std::chrono::high_resolution_clock::now();
        if (current_time - last_cycle_time >= cycle_duration) {
            main_game.executeGame();
            last_cycle_time = current_time;
        }

        // Update timers at 60Hz
        auto current_time_timer = std::chrono::high_resolution_clock::now();
        if (current_time_timer - last_timer_update_time >= timer_update_duration) {
            last_timer_update_time = current_time_timer;
        }


        // Rendering
        if (display.need_to_redraw()) {
            // Clear SDL renderer to black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Get the Chip-8 display pixel data
            const auto& pixels = display.get_display(); // Get const reference to bool[][]

            // Set drawing color to white for pixels
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Draw each active Chip-8 pixel as a scaled SDL_Rect
            for (int y = 0; y < CHIP8_HEIGHT; ++y) {
                for (int x = 0; x < CHIP8_WIDTH; ++x) {
                    if (pixels[y][x]) {
                        SDL_Rect pixel_rect = {x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE};
                        SDL_RenderFillRect(renderer, &pixel_rect);
                    }
                }
            }

            // Present the rendered content to the window
            SDL_RenderPresent(renderer);

            // Reset the redraw flag after drawing
            display.reset_redraw_flag();
        }
    }

    // 7. Cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
