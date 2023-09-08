/*
 * PlayingBar.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#ifndef PLAYINGBAR_H_
#define PLAYINGBAR_H_

#include "raylib.h"
#include "MovingEntity.h"
#include "RoundedRect.h"

class PlayingBar final : public MovingEntity, public RoundedRect {
private:
	Color color;

	constexpr static Vector2 kPlayingBarSpeed = {7.0f, 0.0f};
	constexpr static float kPlayingBarWidth = 100.0f;
	constexpr static float kPlayingBarHeight = 20.0f;
	constexpr static float kPlayingBarRoundness = 0.2f;
	constexpr static float kPlayingBarSegments = 0.0f;
	
public:
	PlayingBar(const Color& color);
	void Move() override;
	void Draw() override;
};

// Getting intial y-axis position of playing bar 
inline float PlayingBarPosY(const float& screen_height) {
    return screen_height - 50;
}

#endif // PLAYINGBAR_H_ 
