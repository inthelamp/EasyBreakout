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

#include "WindowManager.h"

class MovingEntity
{
public:
	static const float kSpeedIncrementRate; // Speed increment rate to automatically change the speed according to game level

	MovingEntity(const Vector2 &speed) { this->speed = speed; }
	virtual ~MovingEntity() {}

	const Vector2 &get_speed() const & { return speed; }
	Vector2 get_speed() && { return std::move(speed); }
	float get_speed_x() { return speed.x; }
	void set_speed(const Vector2 &speed) { this->speed = speed; }
	void set_speed(Vector2 &&speed) { this->speed = std::move(speed); }

	virtual void Move() = 0;

private:
	Vector2 speed;
};

#endif // MOVING_OBJECT_