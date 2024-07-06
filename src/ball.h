/*
 * ball.h
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#ifndef BALL_H_
#define BALL_H_

#include <cmath>
#include <memory>

#include "raylib.h"

#include "screen.h"
#include "moving_entity.h"
#include "graphics_entity.h"
#include "hud.h"
#include "circle.h"
#include "block.h"
#include "tutorial_condition.h"

// Initial ball speed on x-axis
inline float ball_inital_speed_x() { return 2.0f * Screen::scale().x; }
// Initial ball speed on y-axis
inline float ball_inital_speed_y() { return -6.0f * Screen::scale().y; }

// Getting random rate of speed on x-axis
inline float random_speed_rate_x()
{
	return GetRandomValue(5 * Screen::scale().x, 27 * Screen::scale().x) / 10.0f * Screen::scale().x;
}

class Ball : public MovingEntity, public GraphicsEntity<Circle>
{
public:
	Ball(const Sound &hit_bar_sound, const Sound &hit_block_sound, const Color &color, float pos_y, const Vector2 &speed);

	std::shared_ptr<TutorialCondition> tutorial_condition = std::make_shared<TutorialCondition>();

	const Sound &hit_bar_sound() const { return hit_bar_sound_; }
	const Sound &hit_block_sound() const { return hit_block_sound_; }
	bool held() { return held_; }
	void held(bool held) { held_ = held; }
	bool enabled() { return enabled_; }
	void enabled(bool enabled) { enabled_ = enabled; }
	int risk_rate() { return risk_rate_; }
	void risk_rate(int rate) { risk_rate_ = rate; }

	void default_position(float pos_y) { GraphicsEntity::position({(float)Screen::window_size().width / 2, pos_y - shape().radius()}); }

	// Checking collision with blocks and returning the block number hit, otherwise returning -1
	int block_collided_with(Block *blocks, int number_of_blocks);

	bool IsCollided(const Rectangle &rec);						 // Checking collision with rectangle
	void Collide(const Rectangle &rec, const Vector2 &speed);	 // Colliding with rectangle
	void Collide(HUD *hud, const Rectangle &rec, int level_num); // Colliding with playing bar for mobile
	void Collide(const Rectangle &rec, int level_num);			 // Colliding with playing bar

	void PlayHitBarSound();
	void PlayHitBlockSound();

	Circle Scale(Circle &&shape) override;
	void Move() override;
	void Draw() override;

private:
	constexpr static float kRadius = 10.0f; // Ball radius
	static Circle circle()
	{
		return std::move(Circle(kRadius));
	}
	static Vector2 position(float pos_y)
	{
		return {Screen::window_size().width / 2.0f - kRadius * Screen::scale().x, pos_y - kRadius * Screen::scale().x};
	}

	Sound hit_bar_sound_;	// Sound when it hits playing bar
	Sound hit_block_sound_; // Sound when it hits blocks
	Color color_;
	bool held_ = true;	  // Ball doesn't go out if playing bar is holding it
	bool enabled_ = true; // Enabled to crush blocks, preventing from falling other blocks nearby accidently
	int risk_rate_ = 0;	  // Risk rate

	// Angle of bouncing ball depends on the speed on x-axis, so getting its random speed
	float random_speed_x(const Vector2 &speed, int level_num);
};

#endif // BALL_H_
