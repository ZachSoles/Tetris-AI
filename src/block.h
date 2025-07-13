#include <vector>

enum class BlockType {
    I = 1,
    O = 2,
    T = 3,
    S = 4,
    Z = 5,
    J = 6,
    L = 7
};

struct coord {
    int x;
    int y;
};

// T Block Vectors
const std::vector<coord> T_BLOCK_0_DEG = { {1,0}, {0,1}, {1,1}, {2,1} };
const std::vector<coord> T_BLOCK_90_DEG = { {1,0}, {1,1}, {1,2}, {2,1} };
const std::vector<coord> T_BLOCK_180_DEG = { {0,0}, {1,0}, {2,0}, {1,1} };
const std::vector<coord> T_BLOCK_270_DEG = { {0,1}, {1,0}, {1,1}, {1,2} };

// I Block Vectors
const std::vector<coord> I_BLOCK_0_DEG = { {0,0}, {1,0}, {2,0}, {3,0} };
const std::vector<coord> I_BLOCK_90_DEG = { {1,0}, {1,1}, {1,2}, {1,3} };

// S Block Vectors
const std::vector<coord> S_BLOCK_0_DEG = { {1,0}, {2,0}, {0,1}, {1,1} };
const std::vector<coord> S_BLOCK_90_DEG = { {0,0}, {0,1}, {1,1}, {1,2} };

// L Block Vectors
const std::vector<coord> L_BLOCK_0_DEG = { {0,0}, {1,0}, {2,0}, {2,1} };
const std::vector<coord> L_BLOCK_90_DEG = { {1,0}, {1,1}, {1,2}, {0,2} };
const std::vector<coord> L_BLOCK_180_DEG = { {2,0}, {0,1}, {1,1}, {2,1} };
const std::vector<coord> L_BLOCK_270_DEG = { {0,0}, {0,1}, {0,2}, {1,0} };

// J Block Vectors
const std::vector<coord> J_BLOCK_0_DEG = { {0,1}, {1,1}, {2,1}, {0,0} };
const std::vector<coord> J_BLOCK_90_DEG = { {1,0}, {1,1}, {1,2}, {2,2} };
const std::vector<coord> J_BLOCK_180_DEG = { {0,0}, {0,1}, {1,1}, {2,1} };
const std::vector<coord> J_BLOCK_270_DEG = { {0,0}, {1,0}, {0,1}, {0,2} };

// Z Block Vectors
const std::vector<coord> Z_BLOCK_0_DEG = { {0,0}, {1,0}, {1,1}, {2,1} };
const std::vector<coord> Z_BLOCK_90_DEG = { {1,0}, {0,1}, {1,1}, {0,2} };

// O Block Vectors
const std::vector<coord> O_BLOCK_0_DEG = { {0,0}, {1,0}, {1,1}, {0,1} };

class Block {
    private:
        coord global_pos;
        int curr_rotation_state;

    public:
        Block();
        BlockType type;
        std::vector<coord> curr_vector;
        void setBlockType(BlockType type);
        void rotateBlock(int rotate_pos);
        int getRotationState();
        void moveLeft();
        void moveRight();
        void moveDown();
        void setGlobalPosition(coord pos);
        std::vector<coord> getCoordinates();
}
