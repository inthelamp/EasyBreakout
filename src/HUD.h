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

#include "TouchPoint.h"

class HUD
{
public:
	HUD();

	int current_gesture() { return current_gesture_; }
	int last_gesture() { return last_gesture_; }
	const TouchPoint &left_touch_point() const { return left_touch_point_; }
	const TouchPoint &right_touch_point() const { return right_touch_point_; }
	void set_current_gesture(int gesture) { current_gesture_ = gesture; }
	void set_last_gesture(int gesture) { current_gesture_ = gesture; }

	bool IsTouchPointTouched(const TouchPoint &tp) const;
	void Draw();

private:
	int current_gesture_ = GESTURE_NONE;
	int last_gesture_ = GESTURE_NONE;
	TouchPoint left_touch_point_;
	TouchPoint right_touch_point_;
};

#endif // HUD_H_