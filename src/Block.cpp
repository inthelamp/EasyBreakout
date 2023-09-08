/*
 * Block.cpp
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include <iostream>
#include "raylib.h"
#include "EasyBreakout.h"
#include "MovingEntity.h"
#include "Block.h"

Block :: Block() : MovingEntity({0.0f, BLOCK_FALLING_SPEED}), RoundedRect(kBlockWidth, kBlockHeight, kBlockRoundness, kBlockSegments), 
	// Setting random color, avoiding white color
	color({ (unsigned char) GetRandomValue(0, 254), (unsigned char) GetRandomValue(0, 254), (unsigned char) GetRandomValue(0, 254), 0xff }),
	// Setting random points
	point(GetRandomValue(50, 200)) {
}

Block :: Block(const Color& color, const int& points, const Vector2& position) : MovingEntity({0.0f, BLOCK_FALLING_SPEED}), 
				RoundedRect(position, kBlockWidth, kBlockHeight, kBlockRoundness, kBlockSegments), 
				color(color), point(points) {
}

void Block :: Draw() {
	if (!disabled) {
		DrawRectangleRounded(this->get_rec(), this->get_roundness(), (int)this->get_segments(), color);
		if (falling) {
			DrawText(std::to_string(this->get_point()).c_str(), this->get_rec().x + this->get_rec().width/3, this->get_rec().y + 6, 20, COMPLEMENTARY_COLOR(color.r, color.g, color.b));
		}
	}
}

void Block :: Move() {
	auto position = this->get_position();

	if (position.y > PLAYING_BAR_POS_Y) {
		this->set_disabled();
	} 
	else {
		position.y += BLOCK_FALLING_SPEED;
		this->set_position(position);
	}
}