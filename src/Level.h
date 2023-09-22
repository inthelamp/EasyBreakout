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

inline int MaxNumBlocksInRow() {
    return (int)(SCREEN_WIDTH / (Block::kBlockWidth + Block::kBlockColumnOffset));
} 

class Level : public GraphicsEntity {    
private:
    constexpr static float kStartPosY = 50.0f; // Position on y-axis where the first row of blocks starts

    Block * blocks;
    const int level_num;                        // Representing its level
    const Color background_color;               // Background color of game    
    const int number_of_blocks;                 // The number of blocks to hit in the level
    const Vector2 ball_speed;                   // Ball speed of level    

public:    
	constexpr static int kMaxLevelNumber = 10; // Maximum level number to be reached

    Level(const Color& background_color, const int& level_num, const int& number_of_blocks);
    Level(const Color& background_color, const int& level_num, const int& number_of_blocks, const Vector2& ball_speed);
    virtual ~Level() {
        delete[] blocks;
    }
  
    Block * get_blocks() { return blocks; }
	const int& get_level_num() const { return level_num; }
    const Color& get_background_color() const & { return background_color; }
	Color get_background_color() && { return std::move(background_color); }    
    const int& get_number_of_blocks() const { return number_of_blocks; }      
    const Vector2& get_ball_speed() const & { return ball_speed; }
	Vector2 get_ball_speed() && { return std::move(ball_speed); }

    bool is_level_finished();

    void Draw() override;
    void Fall();                                // Block is falling after collision
};

#endif // LEVEL_H_ 