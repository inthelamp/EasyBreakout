/*
 * Ball.h
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#ifndef BALL_H_
#define BALL_H_

#include "raylib.h"
#include "MovingEntity.h"
#include "Circle.h"
#include "Level.h"

class Ball final : public MovingEntity, public Circle {
private:
	Color color;
	bool  held = true;	// Ball doesn't go out if playing bar is holding it 
	bool  enabled = true; // Enabled to crush blocks, preventing from falling other blocks nearby accidently

	// Angle of bouncing ball depends on the speed on x-axis, so getting its random speed	
	const float RandomSpeedOnX(const float& speed_x, const int& level_num) const;  

public:
	Ball (const Color& color, const int& radius, const Vector2& position, const Vector2& speed);
	
	void Move() override;
	void Draw() override;

	bool IsCollided(const Rectangle& rec) const;						// Checking collision with rectangle
	void Collide(const Rectangle& rec, const Vector2& speed);			// Colliding with rectangle 

	// Checking collision with blocks and returning the block number hit, otherwise returning -1
	const int IsCollided(Block * blocks, const int& number_of_blocks);  
	void Collide(const Rectangle& rec, const int& level_num);			// Colliding with playing bar		

	bool IsHeld() const;
	bool IsEnabled() const;

	void set_released() { held = false; }
	void set_disabled() { enabled = false; }
};

#endif // BALL_H_
