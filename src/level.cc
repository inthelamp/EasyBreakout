/*
 * level.cc
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#if defined(EMSCRIPTEN)
#include <iostream>
#endif

#include "level.h"

Level::Level(int level_num, int number_of_blocks, const Color &background_color) : level_num_(level_num), number_of_blocks_(number_of_blocks)
{
    ball_speed_ = {ball_inital_speed_x() + random_speed_rate_x() + level_num * MovingEntity::kSpeedIncrementRate, ball_inital_speed_y() - level_num * MovingEntity::kSpeedIncrementRate};

    background_color_ = background_color;

    // Setting starting position
    float pos_x;
    if (number_of_blocks >= max_num_of_blocks_in_row())
    {
        pos_x = (Screen::window_size().width - (Block::block_width() + column_offset()) * max_num_of_blocks_in_row()) / 2;
    }
    else
    {
        pos_x = (Screen::window_size().width - (Block::block_width() + column_offset()) * number_of_blocks) / 2;
    }
    first_row_start_position_ = {pos_x, kFirstRowStartPosY};

    // Allocating blocks
    blocks_ = new (std::nothrow) Block[number_of_blocks];
    if (blocks_ == nullptr)
    {
        // error assigning memory. Take measures.
        throw("Memory allocation failure!!");
    }

#if defined(EMSCRIPTEN)
    //     std::cout << "Scale " << Screen::scale().x << ", " << Screen::scale().y << std::endl;
    //     std::cout << "ball_inital_speed_x, ball_inital_speed_y: " << ball_inital_speed_x() << ", " << ball_inital_speed_y() << std::endl;
    //     std::cout << "ball speed: " << ball_speed_.x << ", " << ball_speed_.y << std::endl;
    //     std::cout << "column_offset(), row_offset(): " << column_offset() << ", " << row_offset() << std::endl;
    //     std::cout << "level_num, number_of_blocks: " << level_num_ << ", " << number_of_blocks_ << std::endl;
    //     std::cout << "num_of_disabled_blocks_: " << num_of_disabled_blocks_ << std::endl;
    std::cout << "Window width, Window height: " << Screen::web_window_size().width << ", " << Screen::web_window_size().height << std::endl;
#endif
}

Level::Level(const Level &that)
{
    num_of_disabled_blocks_ = that.num_of_disabled_blocks_;
    level_num_ = that.level_num_;
    number_of_blocks_ = that.number_of_blocks_;
    ball_speed_ = that.ball_speed_;
    background_color_ = that.background_color_;
    first_row_start_position_ = that.first_row_start_position_;
    Block *local_blocks = new Block[number_of_blocks_];
    *local_blocks = *that.blocks_;
    delete[] blocks_;
    blocks_ = local_blocks;
}

Level::Level(Level &&that) noexcept
{
    num_of_disabled_blocks_ = std::exchange(that.num_of_disabled_blocks_, 0);
    level_num_ = std::exchange(that.level_num_, 0);
    number_of_blocks_ = std::exchange(that.number_of_blocks_, 0);
    ball_speed_ = std::move(that.ball_speed_);
    background_color_ = std::move(that.background_color_);
    first_row_start_position_ = std::move(that.first_row_start_position_);
    blocks_ = std::move(that.blocks_);
}

Level &Level::operator=(const Level &that)
{
    num_of_disabled_blocks_ = that.num_of_disabled_blocks_;
    level_num_ = that.level_num_;
    number_of_blocks_ = that.number_of_blocks_;
    ball_speed_ = that.ball_speed_;
    background_color_ = that.background_color_;
    first_row_start_position_ = that.first_row_start_position_;
    Block *local_blocks = new Block[number_of_blocks_];
    *local_blocks = *that.blocks_;
    delete[] blocks_;
    blocks_ = local_blocks;
    return *this;
}

Level::Level(int level_num, int number_of_blocks, const Vector2 &ball_speed, const Color &background_color) : level_num_(level_num), number_of_blocks_(number_of_blocks), ball_speed_(ball_speed), background_color_(background_color)
{
    // Setting starting position
    float pos_x;
    if (number_of_blocks >= max_num_of_blocks_in_row())
    {
        pos_x = (Screen::window_size().width - (Block::block_width() + column_offset()) * max_num_of_blocks_in_row()) / 2;
    }
    else
    {
        pos_x = (Screen::window_size().width - (Block::block_width() + column_offset()) * number_of_blocks) / 2;
    }
    first_row_start_position_ = {pos_x, kFirstRowStartPosY};

    // Allocating blocks
    blocks_ = new (std::nothrow) Block[number_of_blocks];
    if (blocks_ == nullptr)
    {
        // error assigning memory. Take measures.
        throw("Memory allocation failure!!");
    }
}

void Level::Draw()
{
    const Vector2 &level_start_position = first_row_start_position_;
    const int max_num_of_rows_with_full_columns = (int)number_of_blocks_ / max_num_of_blocks_in_row();
    int current_column_num = 0; // Starting with 0

    if (max_num_of_rows_with_full_columns == 0)
    { // Only one row
        for (int i = 0; i < number_of_blocks_; ++i)
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
            if (!blocks_[i].falling() && !blocks_[i].disabled())
                blocks_[i].GraphicsEntity::position(position);
            blocks_[i].Draw();
        }
    }
    else
    { // More than one row
        const int number_of_remain_blocks = number_of_blocks_ - max_num_of_rows_with_full_columns * max_num_of_blocks_in_row();
        const float last_row_start_pos_x = (Screen::window_size().width - (Block::block_width() + column_offset()) * number_of_remain_blocks) / 2;
        int current_row_num = 0; // Starting with 0

        for (int i = 0; i < number_of_blocks_; ++i)
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
            if (!blocks_[i].falling() && !blocks_[i].disabled())
                blocks_[i].GraphicsEntity::position(position);
            blocks_[i].Draw();
        }
    }
}

void Level::Fall()
{
    for (int i = 0; i < number_of_blocks_; ++i)
    {
        if (blocks_[i].falling() && !blocks_[i].disabled())
        {
            blocks_[i].Move();
            if (blocks_[i].GraphicsEntity::position().y >= Screen::window_size().height)
            {
                blocks_[i].disabled(true);
                ++num_of_disabled_blocks_;
            }
        }
    }
}

bool Level::IsLevelFinished()
{
    return (num_of_disabled_blocks_ == number_of_blocks_);
}