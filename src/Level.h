/*
 * Level.h
 *
 *  Created on: Aug. 30, 2023
 *      Author: Dong Won Kim
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "raylib.h"
#include "EasyBreakout.h"
#include "GraphicsEntity.h"
#include "Block.h"

#define START_POS_Y             50.0f
#define MAX_NUM_BLOCKS_IN_ROW   ((int)(SCREEN_WIDTH / (Block::kBlockWidth + Block::kBlockColumnOffset)))

class Level : public GraphicsEntity {
private:
	constexpr static int kMaxLevelNumber = 20;

    Block * blocks;
    const int level_num;                        // Representing its level
    const int number_of_blocks;                 // The number of blocks to hit in the level
    const Vector2 ball_speed;                   // Ball speed of level

public:    
    Level(const int& level_num, const int& number_of_blocks);
    Level(const int& level_num, const int& number_of_blocks, const Vector2& ball_speed);
    virtual ~Level() {
        delete[] blocks;
    }
  
    Block * get_blocks() { return blocks; }
	const int& get_level_num() const { return level_num; }
    const int& get_number_of_blocks() const { return number_of_blocks; }      
    const Vector2& get_ball_speed() const & { return ball_speed; }
	Vector2 get_ball_speed() && { return std::move(ball_speed); }

    void Draw() override;
    void Fall();                                // Block is falling after collision
};

#endif // LEVEL_H_ 