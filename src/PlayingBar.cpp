/*
 * PlayingBar.cpp
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include "PlayingBar.h"

PlayingBar::PlayingBar(const Color &color) : MovingEntity((Vector2){kPlayingBarSpeedOnX, 0.0f}), RoundedRect(rectangle(), kPlayingBarRoundness, kPlayingBarSegments), color(color) {}

void PlayingBar::set_speed(int level_num)
{
	const float speed_on_x = (float)kPlayingBarSpeedOnX + level_num * kSpeedIncrementRate * 2;
	MovingEntity::set_speed((Vector2){speed_on_x, 0.0f});
}

bool PlayingBar::IsPlayingBarTouched()
{
	const Vector2 position = get_position();
	return (GetTouchX() >= position.x && GetTouchX() <= position.x + get_shape().width) && (GetTouchY() >= position.y && GetTouchY() <= position.y + get_shape().height) ? true : false;
}

void PlayingBar::Move()
{
	auto pos_x = get_position_x();

	if (IsKeyDown(KEY_LEFT) && (pos_x > 0.0f))
	{
		pos_x -= get_speed_x();
		set_position_x(pos_x);
	}

	if (IsKeyDown(KEY_RIGHT) && (pos_x < (WindowManager::window_size().width - kPlayingBarSize.width * WindowManager::scale().x)))
	{
		pos_x += get_speed_x();
		set_position_x(pos_x);
	}
}

void PlayingBar::Move(const HUD &hud)
{
	auto pos_x = get_position_x();

	if (hud.IsControlPointTouched(hud.left_control()) && pos_x > 0.0f)
	{
		pos_x -= get_speed_x();
		set_position_x(pos_x);
	}

	if (hud.IsControlPointTouched(hud.right_control()) && pos_x < (WindowManager::window_size().width - kPlayingBarSize.width * WindowManager::scale().x))
	{
		pos_x += get_speed_x();
		set_position_x(pos_x);
	}
}

void PlayingBar::Draw()
{
	DrawRectangleRounded(this->get_shape(), get_roundness(), (int)get_segments(), Fade(color, 0.4f));
}