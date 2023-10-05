/*
 * PlayingBar.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYINGBAR_H_
#define PLAYINGBAR_H_

#include "raylib.h"

#include "WindowManager.h"
#include "MovingEntity.h"
#include "RoundedRect.h"

class PlayingBar final : public MovingEntity, public RoundedRect
{
public:
	PlayingBar(const Color &color);

	void set_speed(int level_num);
	void set_default_position() { set_position((Vector2){(float)WindowManager::window_size().width / 2 - (kPlayingBarSize.width * WindowManager::scale().x) / 2, WindowManager::window_size().height - 50 * WindowManager::scale().y}); }

	void Move() override;
	void Draw() override;

private:
	constexpr static Size kPlayingBarSize = (Size){100, 20};
	constexpr static float kPlayingBarSpeedOnX = 7.0f;
	constexpr static float kPlayingBarRoundness = 0.2f;
	constexpr static float kPlayingBarSegments = 0.0f;

	Color color;

	static Rectangle rectangle()
	{
		return (Rectangle){(float)WindowManager::window_size().width / 2 - (kPlayingBarSize.width * WindowManager::scale().x) / 2, WindowManager::window_size().height - 50 * WindowManager::scale().y, kPlayingBarSize.width, kPlayingBarSize.height};
	}
};

#endif // PLAYINGBAR_H_
