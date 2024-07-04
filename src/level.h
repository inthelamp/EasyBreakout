/*
 * level.h
 *
 *  Created on: Aug. 30, 2023
 *      Author: Dong Won Kim
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <iterator>

#include "raylib.h"

#include "screen.h"
#include "ball.h"
#include "block.h"

inline float column_offset() { return 1.0f * Screen::scale().x; }
inline float row_offset() { return 1.0f * Screen::scale().y; }

class Level
{
public:
    constexpr static int kMaxLevelNumber = 10; // Maximum level number to be reached

    Level(int level_num, int number_of_blocks, const Color &background_color);
    Level(int level_num, int number_of_blocks, const Vector2 &ball_speed, const Color &background_color);
    Level(const Level &);                // Copy constructor
    Level(Level &&) noexcept;            // Move constructor
    Level &operator=(const Level &);     // Copy assignment operator
    Level &operator=(Level &&) = delete; // Move assignment operator
    ~Level()
    {
        delete[] blocks_;
    }

    Block *blocks() { return blocks_; }
    int level_num() { return level_num_; }
    int number_of_blocks() { return number_of_blocks_; }
    const Vector2 &ball_speed() const { return ball_speed_; }
    const Color &background_color() const { return background_color_; }

    bool IsLevelFinished();
    void Draw();
    void Fall(); // Block is falling after collision

private:
    constexpr static float kFirstRowStartPosY = 50.0f; // Position on y-axis where the first row of blocks starts

    int num_of_disabled_blocks_ = 0;   // Number of disabled blocks
    int level_num_;                    // Representing its level
    int number_of_blocks_;             // The number of blocks to hit in the level
    Vector2 ball_speed_;               // Ball speed of level
    Color background_color_;           // Background color of game
    Vector2 first_row_start_position_; // Position on x-axis where the first row of blocks starts
    Block *blocks_{nullptr};

    int max_num_of_blocks_in_row() { return (int)(Screen::window_size().width / (Block::block_width() + column_offset())); }
};

#endif // LEVEL_H_
