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

	std::shared_ptr<TutorialCondition> tutorial_condition = std::make_shared<TutorialCondition>();

	void speed(int level_num);
	void default_position() { GraphicsEntity::position({(float)Screen::window_size().width / 2 - (kPlayingBarSize.width * Screen::scale().x) / 2, Screen::window_size().height - 50 * Screen::scale().y}); }

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
};

#endif // PLAYINGBAR_H_
