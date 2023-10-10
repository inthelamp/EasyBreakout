/*
 * HUD.cpp
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#ifndef HUD_H_
#define HUD_H_

#include <iostream>

#include "raylib.h"

#include "ControlPoint.h"

inline Vector2 left_control_position()
{
	return (Vector2){100 * WindowManager::scale().x, WindowManager::window_size().height - WindowManager::window_size().height / 3.0f};
}

inline Vector2 right_control_position()
{
	return (Vector2){WindowManager::window_size().width - 100 * WindowManager::scale().x, WindowManager::window_size().height - WindowManager::window_size().height / 3.0f};
}

inline Vector2 hit_back_control_position()
{
	return (Vector2){ControlPoint::kDefaultRadius * WindowManager::scale().x, WindowManager::window_size().height - WindowManager::window_size().height / 3.0f - ControlPoint::kDefaultRadius * WindowManager::scale().x};
}

class HUD
{
public:
	int current_gesture() { return current_gesture_; }
	int last_gesture() { return last_gesture_; }
	const ControlPoint &left_control() const { return left_control_; }
	const ControlPoint &right_control() const { return right_control_; }
	const ControlPoint &hit_back_control() const { return hit_back_control_; }
	void set_current_gesture(int gesture) { current_gesture_ = gesture; }
	void set_last_gesture(int gesture) { current_gesture_ = gesture; }

	bool IsControlPointTouched(const ControlPoint &tp) const;
	void Draw();

private:
	int current_gesture_ = GESTURE_NONE;
	int last_gesture_ = GESTURE_NONE;
	ControlPoint left_control_ = ControlPoint(left_control_position());			// Move to left
	ControlPoint right_control_ = ControlPoint(right_control_position());		// Move to right
	ControlPoint hit_back_control_ = ControlPoint(hit_back_control_position()); // Hit ball back to the same direction
};

#endif // HUD_H_