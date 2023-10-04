/*
 * Ball.h
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#ifndef BALL_H_
#define BALL_H_

#include <cmath>
#include <memory>

#include "raylib.h"

#include "WindowManager.h"
#include "MovingEntity.h"
#include "GraphicsEntity.h"
#include "Circle.h"
#include "Block.h"

// Initial ball speed on x-axis
inline float ball_inital_speed_x() { return 2.0f * WindowManager::scale().x; }
// Initial ball speed on y-axis
inline float ball_inital_speed_y() { return -6.0f * WindowManager::scale().y; }

// Getting random rate of speed on x-axis
inline float random_speed_rate_x()
{
	return GetRandomValue(5 * WindowManager::scale().x, 27 * WindowManager::scale().x) / 10.0f * WindowManager::scale().x;
}

class Ball final : public MovingEntity, public GraphicsEntity<Circle>
{
public:
	Ball(const Sound &hit_bar_sound, const Sound &hit_block_sound, const Color &color, float pos_y, const Vector2 &speed);

	bool is_held() { return held; }
	bool is_enabled() { return enabled; }
	int get_risk_rate() { return risk_rate; }

	void set_risk_rate(int rate) { risk_rate = rate; }
	void set_held(bool held) { this->held = held; }
	void set_enabled(bool enabled) { this->enabled = enabled; }

	void set_default_position(float pos_y) { set_position((Vector2){(float)WindowManager::window_width() / 2, pos_y - get_shape().get_radius()}); }

	bool IsCollided(const Rectangle &rec);					  // Checking collision with rectangle
	void Collide(const Rectangle &rec, const Vector2 &speed); // Colliding with rectangle

	// Checking collision with blocks and returning the block number hit, otherwise returning -1
	int CollidedBlock(Block *blocks, int number_of_blocks);
	void Collide(const Rectangle &rec, int level_num); // Colliding with playing bar
	void PlayHitBarSound() { PlaySound(hit_bar_sound); }
	void PlayHitBlockSound() { PlaySound(hit_block_sound); }

	Circle Scale(Circle &&shape) override;
	void Move() override;
	void Draw() override;

private:
	constexpr static float kRadius = 10.0f; // Ball radius

	Sound hit_bar_sound;   // Sound when it hits playing bar
	Sound hit_block_sound; // Sound when it hits blocks
	Color color;
	bool held = true;	 // Ball doesn't go out if playing bar is holding it
	bool enabled = true; // Enabled to crush blocks, preventing from falling other blocks nearby accidently
	int risk_rate = 0;	 // Risk rate

	static Circle circle()
	{
		return std::move(Circle(kRadius));
	}

	static Vector2 position(float pos_y)
	{
		return (Vector2){WindowManager::window_width() / 2.0f - kRadius * WindowManager::scale().x, pos_y - kRadius * WindowManager::scale().x};
	}

	// Angle of bouncing ball depends on the speed on x-axis, so getting its random speed
	float RandomSpeedX(const Vector2 &speed, int level_num);
};

#endif // BALL_H_
