/*
 * moving_entity.h
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#ifndef MOVING_ENTITY_
#define MOVING_ENTITY_

#include <utility>

#include "raylib.h"

#include "screen.h"

class MovingEntity
{
public:
	static const float kSpeedIncrementRate; // Speed increment rate to automatically change the speed according to game level

	MovingEntity(const Vector2 &speed);
	MovingEntity(const MovingEntity &) = delete;			// Copy constructor
	MovingEntity(MovingEntity &&) = delete;					// Move constructor
	MovingEntity &operator=(const MovingEntity &) = delete; // Copy assignment operator
	MovingEntity &operator=(MovingEntity &&) = delete;		// Move assignment operator
	virtual ~MovingEntity() = default;

	const Vector2 &speed() const & { return speed_; }
	Vector2 speed() && { return std::move(speed_); }
	float speed_x() { return speed_.x; }
	void speed(const Vector2 &speed) { speed_ = speed; }
	void speed(Vector2 &&speed) { speed_ = std::move(speed); }

	virtual void Move() = 0;

private:
	Vector2 speed_;
};

#endif // MOVING_ENTITY_