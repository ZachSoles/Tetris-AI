#include <array>   // For std::array
#include <cstdint> // For uint8_t
#include <SDL.h>     // Include SDL header
#include <string>

enum class keyMap {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ROTATE,
    PAUSE,
    SPACE,
};

enum class SDL_COLOR {
    NONE,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    BROWN,
    ORANGE,
    PURPLE,
};

const int PIXEL_SCALE = 20;

class SDLHandler {
    private:
    SDL_Renderer* renderer;
    SDL_Window* window;

    std::string screenTitle;
    int screenWidth;
    int screenHeight;

    keyMap lastkeyPressed;
    bool quitRequested = false;


    public:
    SDLHandler(const std::string& str, int width, int height);
    void createWindow();
    int getScreenHeight();
    int getScreenWidth();
    void pollInput();
    keyMap getLastKeyPressed();
    void drawSprite(int x, int y, SDL_COLOR color);
    void close();
    bool getQuitRequested();
};
