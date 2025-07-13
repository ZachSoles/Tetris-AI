#include "block.h"

int Block::getRotationState() { return curr_rotation_state; }

void Block::setBlockType(BlockType type) {
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

void Block::rotateBlock(int rotate_pos) {
    switch (type) {
        case BlockType::I:
            if (rotate_pos == 1) {
                curr_vector = I_BLOCK_0_DEG;
            } else {
                curr_vector = I_BLOCK_90_DEG;
            }
            break;
        case BlockType::T:
            switch (rotate_pos) {
                case 1:
                    curr_vector = T_BLOCK_0_DEG;
                    break;
                case 2:
                    curr_vector = T_BLOCK_90_DEG;
                    break;
                case 3:
                    curr_vector = T_BLOCK_180_DEG;
                    break;
                default:
                    curr_vector = T_BLOCK_270_DEG;
                    break;
            }
            break;
        case BlockType::S:
            if (rotate_pos == 1) {
                curr_vector = S_BLOCK_0_DEG;
            } else {
                curr_vector = S_BLOCK_90_DEG;
            }
            break;
        case BlockType::Z:
            if (rotate_pos == 1) {
                curr_vector = Z_BLOCK_0_DEG;
            } else {
                curr_vector = Z_BLOCK_90_DEG;
            }
            break;
        case BlockType::J:
            switch (rotate_pos) {
                case 1:
                    curr_vector = J_BLOCK_0_DEG;
                    break;
                case 2:
                    curr_vector = J_BLOCK_90_DEG;
                    break;
                case 3:
                    curr_vector = J_BLOCK_180_DEG;
                    break;
                default:
                    curr_vector = J_BLOCK_270_DEG;
                    break;
            }
            break;
        case BlockType::L:
            switch (rotate_pos) {
                case 1:
                    curr_vector = L_BLOCK_0_DEG;
                    break;
                case 2:
                    curr_vector = L_BLOCK_90_DEG;
                    break;
                case 3:
                    curr_vector = L_BLOCK_180_DEG;
                    break;
                default:
                    curr_vector = L_BLOCK_270_DEG;
                    break;
            }
            break;
        default:
            break;
    }
    curr_rotation_state = rotate_pos;
}

void Block::moveLeft() { global_pos.x -= 1; }
void Block::moveRight() { global_pos.x += 1; }
void Block::moveDown() { global_pos.y -= 1; }
void Block::setGlobalPosition(coord pos) { global_pos = pos; }

std::vector<coord> Block::getCoordinates() {
    std::vector<coord> coords = curr_vector;
    for (int i = 0; i < coords.size(); i++) {
        coords[i].x += global_pos.x;
        coords[i].y += global_pos.y;
    }
    
    return coords
}