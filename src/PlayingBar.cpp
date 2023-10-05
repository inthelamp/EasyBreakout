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

void PlayingBar::Move()
{
	auto pos_x = get_position_x();

	if (IsKeyDown(KEY_RIGHT) && (pos_x < (WindowManager::window_size().width - kPlayingBarSize.width * WindowManager::scale().x)))
	{
		pos_x += get_speed_x();
		set_position_x(std::move(pos_x));
	}
	if (IsKeyDown(KEY_LEFT) && (pos_x > 0.0f))
	{
		pos_x -= get_speed_x();
		set_position_x(std::move(pos_x));
	}
}

void PlayingBar::Draw()
{
	DrawRectangleRounded(this->get_shape(), get_roundness(), (int)get_segments(), Fade(color, 0.4f));
}