#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <cstdint>
#include <map>
#include <vector>

const int TOTAL_KEY_COUNT = 5;

enum class TetrisAction {
    None,        // No action
    MoveLeft,
    MoveRight,
    MoveDown,    // Soft Drop
    RotateCW,    // Rotate Clockwise
    RotateCCW,   // Rotate Counter-Clockwise
    HardDrop,
    Hold,        // Hold/Swap piece
    Quit         // Game exit request
};

class Input {
    public:
    Input();

    void update();
    TetrisAction getTetrisAction() const;
    bool shouldQuit() const;

    private:
    const uint8_t* currentKeyboardState;
    // previousKeyboardStateCopy is our own copy of the previous frame's state.
    uint8_t* previousKeyboardStateCopy;

    int last_pressed_key;
    bool quit_requested;
    void initializeKeyBindings();
    std::map<SDL_Scancode, TetrisAction> keyBindings;
}
#endif // INPUT_H
