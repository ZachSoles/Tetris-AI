#include "game.h"
#include <random>

Game::Game() {
    clearGrid();
    // pauseGame();
    int rand_num = getRandNumber(1, NUM_BLOCK_TYPES);
    createNewBlock(rand_num);
}

bool Game::isPaused() { return paused; }
void Game::pauseGame() { paused = true; }
void Game::unPauseGame() { paused = false; }

void Game::executeGame() {
    // Don't perform any logic if the game is paused
    if (paused == true or gameOver == true) {
        return;
    }

    // Get the coordinate for the current block
    std::vector<coord> coords = current_block.getCoordinates();

    if (canFall(coords)) {
        moveDown();
    } else {
        // Add current block to grid
        placeBlock(coords);

        // Find any rows that are filled after placing the current block
        std::vector<int> lines = findLinesToClear(coords);

        // If any rows were filled, then clear the lines and shift the grid
        if (!lines.empty()) {
            clearLines(lines);
        }

        // Generate a random new block type
        int rand_num = getRandNumber(1, NUM_BLOCK_TYPES);
        createNewBlock(rand_num);
        redrawFlag = true;

        // Check to see if the game should be over
        if (shouldGameEnd(coords)) {
            gameOver = true;
            return;
        }
    }
}

int Game::getRandNumber(int min, int max) {
    // Generate a random number to select the next block type
    std::random_device rd;                          // Seed
    std::mt19937 gen(rd());                         // Mersenne Twister engine
    std::uniform_int_distribution<> distr(min, max);    // Range [0, 6]

    return distr(gen);
}

bool Game::canFall(const std::vector<coord>& coords) {
    for (int i = 0; i < coords.size(); i++) {
        if (
            coords[i].y == GRID_HEIGHT - 1 ||
            blockExists(coords[i].x, coords[i].y + 1)
        ) {
            return false;
        }
    }
    return true;
}

bool Game::canMoveLeft(const std::vector<coord>& coords) {
    // Check to see if the block can move left without hitting
    // any other blocks or the edge of the grid
    for (int i = 0; i < coords.size(); i++) {
        if (coords[i].x == 0) {
            return false;
        }

        if (grid[coords[i].y][coords[i].x - 1] != 0) {
            return false;
        }
    }
    return true;
}

bool Game::canMoveRight(const std::vector<coord>& coords) {
    // Check to see if the block can move right without hitting
    // any other blocks or the edge of the grid
    for (int i = 0; i < coords.size(); i++) {
        if (coords[i].x == GRID_WIDTH - 1) {
            return false;
        }

        if (grid[coords[i].y][coords[i].x + 1] != 0) {
            return false;
        }
    }
    return true;
}

void Game::placeBlock(const std::vector<coord>& coords) {
    // Update the values within the grid with the position of the block after moving
    for (int i = 0; i < coords.size(); i++) {
        grid[coords[i].y][coords[i].x] = 1;
    }
}

std::vector<int> Game::findLinesToClear(const std::vector<coord>& coords) {
    std::vector<int> lines;
    // Iterate through cells within current block, and check if any rows within
    // the grid have been filled
    for (int i = 0; i < coords.size(); i++) {
        bool line_filled = true;
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[coords[i].y][j] == 0) {
                line_filled = false;
                break;
            }
        }

        // Add line if no values within row are equal to 0
        if (line_filled) {
            lines.push_back(coords[i].y);
        }
    }

    // Reverse the list of filled lines for better clearing logic
    std::reverse(lines.begin(), lines.end());

    return lines;
}

void Game::clearLines(const std::vector<int>& lines) {
    // Shift all grid cells
    for (int line: lines) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[line][j] = grid[line + 1][j];
        }
    }
}

void Game::clearGrid() {
    // Set all items within the grid to 0
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = 0;
        }
    }
}

void Game::createNewBlock(int blockType) {
    // Set current blocktype to be random block type
    current_block.setBlockType(BlockType(blockType));
    // Set the global position of the current block
    coord newGlobalCoord;
    newGlobalCoord.x = MIDDLE_OF_GRID;
    newGlobalCoord.y = 0;
    current_block.setGlobalPosition(newGlobalCoord);
}

bool Game::shouldGameEnd(const std::vector<coord>& coords) {
    for (int i = 0; i < coords.size(); i++) {
        if (grid[coords[i].y][coords[i].x] == 0) {
            return true;
        }
    }
    return false;
}

void Game::moveLeft() {
    // Exit if unable to move left within game grid
    if (!canMoveLeft(current_block.getCoordinates())) {
        return;
    }

    current_block.moveLeft();
    redrawFlag = true;
}

void Game::moveRight() {
    // Exit if unable to move right within game grid
    if (!canMoveRight(current_block.getCoordinates())) {
        return;
    }

    current_block.moveRight();
    redrawFlag = true;
}

void Game::moveDown() {
    // Exit if unable to move down within the game grid
    if (!canFall(current_block.getCoordinates())) {
        return;
    }

    current_block.moveDown();
    redrawFlag = true;
}

void Game::rotate() {
    current_block.rotateBlock();
    redrawFlag = true;
}

std::vector<coord> Game::getCurrentBlockPosition() {
    return current_block.getCoordinates();
}

bool Game::shouldRedraw() { return redrawFlag; }
void Game::resetRedrawFlag() { redrawFlag = false; }

bool Game::blockExists(int x, int y) {
    return grid[y][x] != 0;
}
