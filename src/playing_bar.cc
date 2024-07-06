/*
 * playing_bar.cc
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include "playing_bar.h"

PlayingBar::PlayingBar(const Color &color) : MovingEntity({kPlayingBarSpeedOnX, 0.0f}), RoundedRect(rectangle(), kPlayingBarRoundness, kPlayingBarSegments), color_(color) {}

void PlayingBar::speed(int level_num)
{
	const float speed_on_x = (float)kPlayingBarSpeedOnX + level_num * kSpeedIncrementRate * 2;
	MovingEntity::speed({speed_on_x, 0.0f});
}

bool PlayingBar::IsPlayingBarTouched()
{
	const Vector2 position = GraphicsEntity::position();
	return (GetTouchX() >= position.x && GetTouchX() <= position.x + shape().width) && (GetTouchY() >= position.y && GetTouchY() <= position.y + shape().height) ? true : false;
}

void PlayingBar::Move()
{
	auto pos_x = position_x();

	if (IsKeyDown(KEY_LEFT) && (pos_x > 0.0f))
	{
		pos_x -= speed_x();
		position_x(pos_x);
	}

	if (IsKeyDown(KEY_RIGHT) && (pos_x < (Screen::window_size().width - kPlayingBarSize.width * Screen::scale().x)))
	{
		pos_x += speed_x();
		position_x(pos_x);
	}
}

void PlayingBar::Move(HUD *hud)
{
	auto pos_x = position_x();

	auto lcp = hud->left_control();
	if (hud->IsControlPointTouched(lcp) && pos_x > 0.0f)
	{
		auto tutorial_condition = lcp->tutorial_condition;
		// Tutorial condition is met
		if (tutorial_condition->started())
		{
			tutorial_condition->achieved(true);
		}
		pos_x -= speed_x();
		position_x(pos_x);
	}

	auto rcp = hud->right_control();
	if (hud->IsControlPointTouched(rcp) && pos_x < (Screen::window_size().width - kPlayingBarSize.width * Screen::scale().x))
	{
		auto tutorial_condition = rcp->tutorial_condition;
		// Tutorial condition is met
		if (tutorial_condition->started())
		{
			tutorial_condition->achieved(true);
		}
		pos_x += speed_x();
		position_x(pos_x);
	}
}

void PlayingBar::Draw()
{
	DrawRectangleRounded(shape(), roundness(), (int)segments(), Fade(color_, 0.4f));
}