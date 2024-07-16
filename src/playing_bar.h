/*
 * playing_bar.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYINGBAR_H_
#define PLAYINGBAR_H_

#include "raylib.h"

#include "screen.h"
#include "moving_entity.h"
#include "rounded_rect.h"
#include "hud.h"
#include "tutorial_condition.h"

class PlayingBar : public MovingEntity, public RoundedRect
{
public:
	PlayingBar(const Color &color);
	PlayingBar(const PlayingBar &) = delete;			// Copy constructor
	PlayingBar(PlayingBar &&) = delete;					// Move constructor
	PlayingBar &operator=(const PlayingBar &) = delete; // Copy assignment operator
	PlayingBar &operator=(PlayingBar &&) = delete;		// Move assignment operator
	~PlayingBar()
	{
		if (Screen::IsMobile())
		{
			delete start_game_;
		}
	}

	// Overloading of MovingEntity::speed
	void speed(int level_num)
	{
		const float speed_on_x = (float)kPlayingBarSpeedOnX + level_num * kSpeedIncrementRate * 2;
		MovingEntity::speed({speed_on_x, 0.0f});
	}

	void InitPosition();
	void InitStartGameCP();
	ControlPoint *start_game() { return start_game_; }
	bool IsPlayingBarTouched();
	void Move() override;
	void Move(HUD *hud); // For mobile
	void Draw() override;

private:
	constexpr static Size kPlayingBarSize = (Size){100, 20};
	constexpr static float kPlayingBarSpeedOnX = 7.0f;
	constexpr static float kPlayingBarRoundness = 0.2f;
	constexpr static float kPlayingBarSegments = 0.0f;
	// Get a rectangle
	static Rectangle rectangle()
	{
		return {(float)Screen::window_size().width / 2 - (kPlayingBarSize.width * Screen::scale().x) / 2, Screen::window_size().height - 50 * Screen::scale().y, kPlayingBarSize.width, kPlayingBarSize.height};
	}

	Color color_;

	ControlPoint *start_game_{nullptr};
};

#endif // PLAYINGBAR_H_
