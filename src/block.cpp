#include "block.h"

int Block::getRotationState() { return curr_rotation_state; }

Block::Block() {

}

void Block::setBlockType(BlockType type) {
    curr_block_type = type;
    switch (type) {
        case BlockType::I:
            curr_vector = I_BLOCK_0_DEG;
            break;
        case BlockType::O:
            curr_vector = O_BLOCK_0_DEG;
            break;
        case BlockType::T:
            curr_vector = T_BLOCK_0_DEG;
            break;
        case BlockType::S:
            curr_vector = S_BLOCK_0_DEG;
            break;
        case BlockType::Z:
            curr_vector = Z_BLOCK_0_DEG;
            break;
        case BlockType::J:
            curr_vector = J_BLOCK_0_DEG;
            break;
        case BlockType::L:
            curr_vector = L_BLOCK_0_DEG;
            break;
    }
}

void Block::rotateBlock() {
    curr_rotation_state += 1;

    switch (curr_block_type) {
        case BlockType::I:
            switch (curr_rotation_state) {
                case 2:
                    curr_vector = I_BLOCK_90_DEG;
                    break;
                default:
                    curr_vector = I_BLOCK_0_DEG;
                    curr_rotation_state = 1;
                    break;
            }
            break;
        case BlockType::T:
            switch (curr_rotation_state) {
                case 2:
                    curr_vector = T_BLOCK_90_DEG;
                    break;
                case 3:
                    curr_vector = T_BLOCK_180_DEG;
                    break;
                case 4:
                    curr_vector = T_BLOCK_270_DEG;
                    break;
                default:
                    curr_vector = T_BLOCK_0_DEG;
                    curr_rotation_state = 1;
                    break;
            }
            break;
        case BlockType::S:
            switch (curr_rotation_state) {
                case 2:
                    curr_vector = S_BLOCK_90_DEG;
                    break;
                default:
                    curr_vector = S_BLOCK_0_DEG;
                    curr_rotation_state = 1;
                    break;
            }
            break;
        case BlockType::Z:
            switch (curr_rotation_state) {
                case 2:
                    curr_vector = Z_BLOCK_90_DEG;
                    break;
                default:
                    curr_vector = Z_BLOCK_0_DEG;
                    curr_rotation_state = 1;
                    break;
            }
            break;
        case BlockType::J:
            switch (curr_rotation_state) {
                case 2:
                    curr_vector = J_BLOCK_90_DEG;
                    break;
                case 3:
                    curr_vector = J_BLOCK_180_DEG;
                    break;
                case 4:
                    curr_vector = J_BLOCK_270_DEG;
                    break;
                default:
                    curr_vector = J_BLOCK_0_DEG;
                    curr_rotation_state = 1;
                    break;
            }
            break;
        case BlockType::L:
            switch (curr_rotation_state) {
                case 2:
                    curr_vector = L_BLOCK_90_DEG;
                    break;
                case 3:
                    curr_vector = L_BLOCK_180_DEG;
                    break;
                case 4:
                    curr_vector = L_BLOCK_270_DEG;
                    break;
                default:
                    curr_vector = L_BLOCK_0_DEG;
                    curr_rotation_state = 1;
                    break;
            }
            break;
        default:
            break;
    }
}

void Block::moveLeft() { global_pos.x -= 1; }
void Block::moveRight() { global_pos.x += 1; }
void Block::moveDown() { global_pos.y += 1; }
void Block::setGlobalPosition(coord pos) { global_pos = pos; }

std::vector<coord> Block::getCoordinates() {
    std::vector<coord> coords = curr_vector;
    for (int i = 0; i < coords.size(); i++) {
        coords[i].x += global_pos.x;
        coords[i].y += global_pos.y;
    }

    return coords;
}
