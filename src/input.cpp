#include "input.h"
#include <iostream> // For error/debug output

Input::Input() {
    last_pressed_key = -1; // No key pressed initially
    quit_requested = false;
}

void Input::initializeKeyBindings() {
    key_map[0]
}

void Input::poll_events() {
    SDL_Event event;
    last_pressed_key = -1; // Reset last_pressed_key at the start of each cycle

    // Loop through all pending SDL events
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit_requested = true;
                break;
 case SDL_KEYDOWN:
                // Ignore key repeats for most Chip-8 games
                if (event.key.repeat == 0) {
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_LEFT:
                        last_pressed_key = 1;
                        break;
                        
                    }
                }
                break;
            default:
                // Handle other event types if necessary (e.g., window resize, mouse)
                break;
        }
    }
}

bool Input::is_pressed(uint8_t chip8_key_code) const {
    if (chip8_key_code >= 0 && chip8_key_code < CHIP8_KEY_COUNT) {
        return key_states[chip8_key_code];
    }
    std::cerr << "Warning: Attempted to check invalid Chip-8 key code: "
              << static_cast<int>(chip8_key_code) << std::endl;
    return false; // Invalid key code
}

int Input::get_pressed_key() const {
    return last_pressed_key;
}

bool Input::should_quit() const {
    return quit_requested;
}
