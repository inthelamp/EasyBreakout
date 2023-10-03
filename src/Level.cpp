/*
 * Level.cpp
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#if defined(EMSCRIPTEN)
#include <iostream>
#endif

#include "Level.h"

Level::Level(int level_num, int number_of_blocks, const Color &background_color) : level_num(level_num), number_of_blocks(number_of_blocks)
{
    ball_speed = (Vector2){ball_inital_speed_x() + random_speed_rate_x() + level_num * MovingEntity::kSpeedIncrementRate, ball_inital_speed_y() - level_num * MovingEntity::kSpeedIncrementRate};

    this->background_color = background_color;

    // Setting starting position
    float pos_x;
    if (number_of_blocks >= max_num_of_blocks_in_row())
    {
        pos_x = (WindowManager::window_width() - (Block::block_width() + column_offset()) * max_num_of_blocks_in_row()) / 2;
    }
    else
    {
        pos_x = (WindowManager::window_width() - (Block::block_width() + column_offset()) * number_of_blocks) / 2;
    }
    first_row_start_position = (Vector2){pos_x, kFirstRowStartPosY};

    // Allocating blocks
    blocks = new (std::nothrow) Block[number_of_blocks];
    if (blocks == nullptr)
    {
        // error assigning memory. Take measures.
        throw("Memory allocation failure!!");
    }

    // #if defined(EMSCRIPTEN)
    //     std::cout << "Scale " << WindowManager::scale().x << ", " << WindowManager::scale().y << std::endl;
    //     std::cout << "ball_inital_speed_x, ball_inital_speed_y: " << ball_inital_speed_x() << ", " << ball_inital_speed_y() << std::endl;
    //     std::cout << "ball speed: " << ball_speed.x << ", " << ball_speed.y << std::endl;
    //     std::cout << "column_offset(), row_offset(): " << column_offset() << ", " << row_offset() << std::endl;
    //     std::cout << "level_num, number_of_blocks: " << level_num << ", " << number_of_blocks << std::endl;
    //     std::cout << "num_of_disabled_blocks: " << num_of_disabled_blocks << std::endl;
    // #endif
}

Level::Level(int level_num, int number_of_blocks, const Vector2 &ball_speed, const Color &background_color) : level_num(level_num), number_of_blocks(number_of_blocks), ball_speed(ball_speed), background_color(background_color)
{

    // Setting starting position
    float pos_x;
    if (number_of_blocks >= max_num_of_blocks_in_row())
    {
        pos_x = (WindowManager::window_width() - (Block::block_width() + column_offset()) * max_num_of_blocks_in_row()) / 2;
    }
    else
    {
        pos_x = (WindowManager::window_width() - (Block::block_width() + column_offset()) * number_of_blocks) / 2;
    }
    first_row_start_position = (Vector2){pos_x, kFirstRowStartPosY};

    // Allocating blocks
    blocks = new (std::nothrow) Block[number_of_blocks];
    if (blocks == nullptr)
    {
        // error assigning memory. Take measures.
        throw("Memory allocation failure!!");
    }
}

void Level::Draw()
{
    const Vector2 &level_start_position = first_row_start_position;
    const int max_num_of_rows_with_full_columns = (int)number_of_blocks / max_num_of_blocks_in_row();
    int current_column_num = 0; // Starting with 0

    if (max_num_of_rows_with_full_columns == 0)
    { // Only one row
        for (int i = 0; i < number_of_blocks; ++i)
        {
            if (i % max_num_of_blocks_in_row() == 0)
            {
                current_column_num = 0;
            }
            else
            {
                ++current_column_num;
            }

            float pos_x = level_start_position.x + (Block::block_width() + column_offset()) * current_column_num;
            float pos_y = level_start_position.y;
            const Vector2 position{pos_x, pos_y};
            if (!blocks[i].is_falling() && !blocks[i].is_disabled())
                blocks[i].set_position(position);
            blocks[i].Draw();
        }
    }
    else
    { // More than one row
        const int number_of_remain_blocks = number_of_blocks - max_num_of_rows_with_full_columns * max_num_of_blocks_in_row();
        const float last_row_start_pos_x = (WindowManager::window_width() - (Block::block_width() + column_offset()) * number_of_remain_blocks) / 2;
        int current_row_num = 0; // Starting with 0

        for (int i = 0; i < number_of_blocks; ++i)
        {
            if (i % max_num_of_blocks_in_row() == 0)
            {
                current_column_num = 0;
                if (i != 0)
                    ++current_row_num;
            }
            else
            {
                ++current_column_num;
            }

            float pos_x;
            if (current_row_num < max_num_of_rows_with_full_columns)
            {
                pos_x = level_start_position.x + (Block::block_width() + column_offset()) * current_column_num;
            }
            else
            {
                pos_x = last_row_start_pos_x + (Block::block_width() + column_offset()) * current_column_num;
            }

            float pos_y = level_start_position.y + (Block::block_height() + column_offset()) * current_row_num;
            const Vector2 position{pos_x, pos_y};
            if (!blocks[i].is_falling() && !blocks[i].is_disabled())
                blocks[i].set_position(position);
            blocks[i].Draw();
        }
    }
}

void Level::Fall()
{
    for (int i = 0; i < number_of_blocks; ++i)
    {
        if (blocks[i].is_falling() && !blocks[i].is_disabled())
        {
            blocks[i].Move();
            if (blocks[i].get_position().y >= WindowManager::window_height())
            {
                blocks[i].set_disabled();
                ++num_of_disabled_blocks;
            }
        }
    }
}

bool Level::IsLevelFinished()
{
    return (num_of_disabled_blocks == number_of_blocks);
}