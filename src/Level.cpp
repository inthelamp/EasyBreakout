/*
 * Level.cpp
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#include <new>
#include "raylib.h"
#include "EasyBreakout.h"
#include "Block.h"
#include "Level.h"

Level :: Level(const int& level_num, const int& number_of_blocks) 
            : level_num(level_num), number_of_blocks(number_of_blocks), 
              ball_speed({(INIT_BALL_SPEED_X + level_num * BALL_SPEED_INCREMENT_RATE) * BALL_RANDOM_SPEED_RATE_ON_X, 
                           INIT_BALL_SPEED_Y + level_num * BALL_SPEED_INCREMENT_RATE}) {

        // Setting starting position    
        float pos_x;                        
        if (number_of_blocks >= MAX_NUM_BLOCKS_IN_ROW) {
            pos_x = (SCREEN_WIDTH - (Block::kBlockWidth + Block::kBlockColumnOffset) * MAX_NUM_BLOCKS_IN_ROW) / 2;
        } else {            
            float pos_x = (SCREEN_WIDTH - (Block::kBlockWidth + Block::kBlockColumnOffset) * number_of_blocks) / 2;
        }
        this->set_position({pos_x, START_POS_Y});        

        // Allocating blocks
        blocks = new (std::nothrow) Block[number_of_blocks];
        if (blocks == nullptr) {
            // error assigning memory. Take measures.
            throw("Memory allocation failure!!");
        }
}

Level :: Level(const int& level_num, const int& number_of_blocks, const Vector2& ball_speed) 
            : level_num(level_num), number_of_blocks(number_of_blocks), ball_speed(ball_speed) {

        // Setting starting position  
        float pos_x;                        
        if (number_of_blocks >= MAX_NUM_BLOCKS_IN_ROW) {
            pos_x = (SCREEN_WIDTH - (Block::kBlockWidth + Block::kBlockColumnOffset) * MAX_NUM_BLOCKS_IN_ROW) / 2;
        } else {            
            float pos_x = (SCREEN_WIDTH - (Block::kBlockWidth + Block::kBlockColumnOffset) * number_of_blocks) / 2;
        }
        this->set_position({pos_x, START_POS_Y});        

        // Allocating blocks
        blocks = new (std::nothrow) Block[number_of_blocks];
        if (blocks == nullptr) {
            // error assigning memory. Take measures.
            throw("Memory allocation failure!!");
        }
}

void Level :: Draw() {   
    const Vector2& level_start_position = this->get_position();
    const int max_num_blocks_in_row = MAX_NUM_BLOCKS_IN_ROW;  
    const int max_num_of_rows_with_full_columns = (int) number_of_blocks / max_num_blocks_in_row;  
    int current_column_num = 0;                         // Starting with 0

    if (max_num_of_rows_with_full_columns == 0) {       // Only one row        
        for (int i = 0; i < this->number_of_blocks; ++i) {
            if (i % max_num_blocks_in_row == 0) {
                current_column_num = 0;
            } else {
                ++current_column_num;
            }

            float pos_x = level_start_position.x + (Block::kBlockWidth + Block::kBlockColumnOffset) * current_column_num;
            float pos_y = level_start_position.y;
            const Vector2 position { pos_x, pos_y }; 
            if (!blocks[i].is_falling() && !blocks[i].is_disabled()) blocks[i].set_position(position);
            blocks[i].Draw();        
        }
    } else {                                            // More than one row
        const int number_of_remain_blocks =  number_of_blocks - max_num_of_rows_with_full_columns * max_num_blocks_in_row;
        const float last_row_start_pos_x = (SCREEN_WIDTH - (Block::kBlockWidth + Block::kBlockColumnOffset) * number_of_remain_blocks) / 2;
        int current_row_num = 0;                        // Starting with 0

        for (int i = 0; i < this->number_of_blocks; ++i) {
            if (i % max_num_blocks_in_row == 0) {
                current_column_num = 0;
                if (i != 0) ++current_row_num;
            } else {
                ++current_column_num;
            }

            float pos_x;
            if ( current_row_num < max_num_of_rows_with_full_columns) {
                pos_x = level_start_position.x + (Block::kBlockWidth + Block::kBlockColumnOffset) * current_column_num;
            } else {
                pos_x = last_row_start_pos_x + (Block::kBlockWidth + Block::kBlockColumnOffset) * current_column_num;
            }

            float pos_y = level_start_position.y + (Block::kBlockHeight + Block::kBlockColumnOffset) * current_row_num;
            const Vector2 position { pos_x, pos_y }; 
            if (!blocks[i].is_falling() && !blocks[i].is_disabled()) blocks[i].set_position(position);
            blocks[i].Draw();        
        }
    }
}

void Level :: Fall() {   
    for (int i = 0; i < this->number_of_blocks; ++i) {
        if (blocks[i].is_falling() && !blocks[i].is_disabled()) blocks[i].Move();        
    }
}