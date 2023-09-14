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

// Getting random rate of speed on x-axis
inline float RandomRateOfSpeedOnX() {
    return GetRandomValue(5, 27) / 10.0f;
}

class Ball final : public MovingEntity, public Circle {

private:
	Color color;
	bool held = true;										// Ball doesn't go out if playing bar is holding it 
	bool enabled = true; 									// Enabled to crush blocks, preventing from falling other blocks nearby accidently
	int risk_rate = 0;										// Risk rate

	// Angle of bouncing ball depends on the speed on x-axis, so getting its random speed	
	const float RandomSpeedOnX(const Vector2& speed, const int& level_num) const;  

	constexpr static float kRadius = 10.0f;                	// Ball radius

public:
	constexpr static float kInitalSpeedOnX = 2.0f;          // Initial ball speed on x-axis 
	constexpr static float kInitalSpeedOnY = -6.0f;         // Initial ball speed on y-axis 
	constexpr static float kSpeedIncrementRate = 0.2f;    	// Ball speed increment due to game level

	Ball (const Color& color, const float& playing_bar_position_y, const Vector2& speed, const int& radius = kRadius);
	
	void Move() override;
	void Draw() override;

	bool IsCollided(const Rectangle& rec) const;						// Checking collision with rectangle
	void Collide(const Rectangle& rec, const Vector2& speed);			// Colliding with rectangle 

	// Checking collision with blocks and returning the block number hit, otherwise returning -1
	const int IsCollided(Block * blocks, const int& number_of_blocks);  
	void Collide(const Rectangle& rec, const int& level_num);			// Colliding with playing bar		

	bool IsHeld() const;
	bool IsEnabled() const;
	const int get_risk_rate() const { return risk_rate; }
	void set_risk_rate(const int& rate) { risk_rate = rate; }

	void set_held(const bool& held) { this->held = held; }
	void set_enabled(const bool& enabled) { this->enabled = enabled; }

	void set_default_position(const float& pos_y) { set_position((Vector2){(float)SCREEN_WIDTH/2, pos_y - get_radius()}); }
};

#endif // BALL_H_
