#include "block.h"

const int GRID_HEIGHT = 24;
const int GRID_WIDTH = 10;
const int GRID_VIEW_HEIGHT = 20;
const int MIDDLE_OF_GRID = 5;
const int NUM_BLOCK_TYPES = 7;

class Game {
    private:
        int grid[GRID_HEIGHT][GRID_WIDTH];
        bool paused;
        bool gameOver;
        Block current_block;
        void clearGrid();
        std::vector<int> findLinesToClear(const std::vector<coord>& coordss);
        void clearLines(const std::vector<int>& lines);
        bool canFall(const std::vector<coord>& coords);
        bool canMoveLeft(const std::vector<coord>& coords);
        bool canMoveRight(const std::vector<coord>& coords);
        void placeBlock(const std::vector<coord>& coords);
        int getRandNumber(int min, int max);
        void createNewBlock(int blockType);
        bool shouldGameEnd(const std::vector<coord>& coords);

    public:
        Game();

        void pauseGame();
        void unPauseGame();
        void executeGame();
        bool isPaused();
        bool isGameOver();
        void moveLeft();
        void moveDown();
        void moveRight();
        void rotate();
        std::vector<coord> getCurrentBlockPosition();
};
