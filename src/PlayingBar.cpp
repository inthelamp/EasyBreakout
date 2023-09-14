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
					: MovingEntity(kPlayingBarSpeed), RoundedRect((Vector2){(float)SCREEN_WIDTH/2 - kPlayingBarWidth/2, PlayingBarPosY(SCREEN_HEIGHT)}, 
																	kPlayingBarWidth, kPlayingBarHeight, kPlayingBarRoundness, kPlayingBarSegments) {
	this->color = color;
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