/*
 * hud.cc
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#ifndef HUD_H_
#define HUD_H_

#include <iostream>

#include "raylib.h"

#include "control_point.h"

inline Vector2 left_control_position()
{
	return {100 * Screen::scale().x, Screen::window_size().height - Screen::window_size().height / 5.0f};
}

inline Vector2 right_control_position()
{
	return {Screen::window_size().width - 100 * Screen::scale().x, Screen::window_size().height - Screen::window_size().height / 5.0f};
}

inline Vector2 hit_back_control_position()
{
	// return {ControlPoint::kDefaultRadius * Screen::scale().x, Screen::window_size().height - Screen::window_size().height / 3.0f - ControlPoint::kDefaultRadius * Screen::scale().x};
	return {100 * Screen::scale().x, Screen::window_size().height - Screen::window_size().height / 2.5f};
}

class HUD
{
public:
	HUD() = default;
	HUD(const HUD &) = delete;			  // Copy constructor
	HUD(HUD &&) = delete;				  // Move constructor
	HUD &operator=(const HUD &) = delete; // Copy assignment operator
	HUD &operator=(HUD &&) = delete;	  // Move assignment operator
	~HUD()
	{
		delete left_control_;
		delete right_control_;
		delete hit_back_control_;
	}

	int current_gesture() { return current_gesture_; }
	int last_gesture() { return last_gesture_; }
	void current_gesture(int gesture) { current_gesture_ = gesture; }
	void last_gesture(int gesture) { current_gesture_ = gesture; }
	ControlPoint *left_control() { return left_control_; }
	ControlPoint *right_control() { return right_control_; }
	ControlPoint *hit_back_control() { return hit_back_control_; }

	void Draw();

private:
	int current_gesture_ = GESTURE_NONE;
	int last_gesture_ = GESTURE_NONE;
	ControlPoint *left_control_ = new ControlPoint(left_control_position());		 // Move to left
	ControlPoint *right_control_ = new ControlPoint(right_control_position());		 // Move to right
	ControlPoint *hit_back_control_ = new ControlPoint(hit_back_control_position()); // Hit ball back to the same direction
};

#endif // HUD_H_