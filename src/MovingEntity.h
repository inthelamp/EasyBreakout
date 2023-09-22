/*
 * MovingEntity.h
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#ifndef MOVING_OBJECT_
#define MOVING_OBJECT_

#include <utility>
#include "raylib.h"

class MovingEntity {
private:
	Vector2 speed;

public:
	constexpr static float kSpeedIncrementRate = 0.2f;    	// Ball speed increment due to game level
	
	MovingEntity(const Vector2& speed) { this->speed = speed; }
	virtual ~MovingEntity() { }

	const Vector2& get_speed() const & { return speed; }
	Vector2 get_speed() && { return std::move(speed); }
	const float& get_speed_x() const & { return speed.x; }
	float get_speed_x() && { return std::move(speed.x); }
	void set_speed(const Vector2& speed) { this->speed = speed; }
	void set_speed(Vector2&& speed) { this->speed = std::move(speed); }
	virtual void Move() = 0;
};

#endif // MOVING_OBJECT_ 