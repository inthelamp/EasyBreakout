/*
 * Block.cpp
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include <iostream>
#include "raylib.h"
#include "EasyBreakout.h"
#include "PlayingBar.h"
#include "MovingEntity.h"
#include "Block.h"

Block :: Block() : MovingEntity({0.0f, kBlockFallingSpeed}), RoundedRect(kBlockWidth, kBlockHeight, kBlockRoundness, kBlockSegments), 
	// Setting random color, avoiding white color
	color({ (unsigned char) GetRandomValue(0, 254), (unsigned char) GetRandomValue(0, 254), (unsigned char) GetRandomValue(0, 254), 0xff }),
	// Setting random points
	point(GetRandomValue(50, 200)) {
}

Block :: Block(const Color& color, const int& points, const Vector2& position) : MovingEntity({0.0f, kBlockFallingSpeed}), 
				RoundedRect(position, kBlockWidth, kBlockHeight, kBlockRoundness, kBlockSegments), 
				color(color), point(points) {
}

void Block :: Draw() {
	if (!disabled) {
		DrawRectangleRounded(this->get_rec(), this->get_roundness(), (int)this->get_segments(), color);
		if (falling) {
			DrawText(std::to_string(this->get_point()).c_str(), this->get_rec().x + this->get_rec().width/3, this->get_rec().y + 6, 20, ComplementaryColor(color));
		}
	}
}

void Block :: Move() {
	auto position = this->get_position();

	if (position.y > PlayingBarPosY(SCREEN_HEIGHT)) {
		this->set_disabled();
	} 
	else {
		position.y += kBlockFallingSpeed;
		this->set_position(position);
	}
}