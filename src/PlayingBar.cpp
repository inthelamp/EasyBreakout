/*
 * PlayingBar.cpp
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include "raylib.h"
#include "EasyBreakout.h"
#include "PlayingBar.h"

PlayingBar :: PlayingBar(const Color& color)
					: MovingEntity((Vector2){kPlayingBarSpeedOnX, 0.0f}), RoundedRect((Vector2){(float)SCREEN_WIDTH/2 - kPlayingBarWidth/2, PlayingBarPosY(SCREEN_HEIGHT)}, 
																	kPlayingBarWidth, kPlayingBarHeight, kPlayingBarRoundness, kPlayingBarSegments) {
	this->color = color;
}

void PlayingBar :: set_speed(int level_num) {
		const float speed_on_x  = (float) kPlayingBarSpeedOnX + level_num * kSpeedIncrementRate * 2;
		MovingEntity :: set_speed((Vector2){speed_on_x, 0.0f});
}

void PlayingBar :: Move() {
	auto pos_x = get_position_x();

    if (IsKeyDown(KEY_RIGHT) && (pos_x < (GetScreenWidth() - kPlayingBarWidth))) {
		pos_x += get_speed_x();
		set_position_x(pos_x);
	}
    if (IsKeyDown(KEY_LEFT) && (pos_x > 0.0f)) {
		pos_x -= get_speed_x();
		set_position_x(pos_x);
	}
}

void PlayingBar :: Draw() {
	DrawRectangleRounded(get_rec(), get_roundness(), (int)get_segments(), Fade(color, 0.2f));
}