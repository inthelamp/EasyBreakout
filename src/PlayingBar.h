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

// Getting intial y-axis position of playing bar 
inline float PlayingBarPosY(const float& screen_height) {
    return screen_height - 50;
}

class PlayingBar final : public MovingEntity, public RoundedRect {
private:
	constexpr static float kPlayingBarSpeedOnX = 7.0f;
	constexpr static float kPlayingBarWidth = 100.0f;
	constexpr static float kPlayingBarHeight = 20.0f;
	constexpr static float kPlayingBarRoundness = 0.2f;
	constexpr static float kPlayingBarSegments = 0.0f;
	
	Color color;
	
public:
	PlayingBar(const Color& color);
	
	void set_speed(int level_num); 
	void set_default_position() { set_position((Vector2){(float)SCREEN_WIDTH/2 - kPlayingBarWidth/2, PlayingBarPosY(SCREEN_HEIGHT)}); }
	void Move() override;
	void Draw() override;
};

#endif // PLAYINGBAR_H_ 
