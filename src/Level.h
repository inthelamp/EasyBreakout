/*
 * Level.h
 *
 *  Created on: Aug. 30, 2023
 *      Author: Dong Won Kim
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <new>

#include "raylib.h"

#include "WindowManager.h"
#include "Ball.h"
#include "Block.h"

inline float column_offset() { return 1.0f * WindowManager::scale().x; }
inline float row_offset() { return 1.0f * WindowManager::scale().y; }

class Level
{
public:
    constexpr static int kMaxLevelNumber = 10; // Maximum level number to be reached

    Level(int level_num, int number_of_blocks, const Color &background_color);
    Level(int level_num, int number_of_blocks, const Vector2 &ball_speed, const Color &background_color);
    ~Level()
    {
        delete[] blocks;
    }

    Block *get_blocks() { return blocks; }
    int get_level_num() { return level_num; }
    int get_number_of_blocks() { return number_of_blocks; }
    const Vector2 &get_ball_speed() const { return ball_speed; }
    const Color &get_background_color() const { return background_color; }

    bool IsLevelFinished();
    void Draw();
    void Fall(); // Block is falling after collision

private:
    constexpr static float kFirstRowStartPosY = 50.0f; // Position on y-axis where the first row of blocks starts

    int num_of_disabled_blocks = 0;   // Number of disabled blocks
    int level_num;                    // Representing its level
    int number_of_blocks;             // The number of blocks to hit in the level
    Vector2 ball_speed;               // Ball speed of level
    Color background_color;           // Background color of game
    Vector2 first_row_start_position; // Position on x-axis where the first row of blocks starts
    Block *blocks;

    int max_num_of_blocks_in_row() { return (int)(WindowManager::window_size().width / (Block::block_width() + column_offset())); }
};

#endif // LEVEL_H_
