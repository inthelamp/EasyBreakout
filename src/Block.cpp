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

int Block :: num_of_disabled_blocks = 0;

Block :: Block() : MovingEntity({0.0f, kBlockFallingSpeed}), RoundedRect(kBlockWidth, kBlockHeight, kBlockRoundness, kBlockSegments), 
					color(RandomColor()), point(RandomPoints()) {
}

Block :: Block(const Color& color, const int& points, const Vector2& position) : MovingEntity({0.0f, kBlockFallingSpeed}), 
				RoundedRect(position, kBlockWidth, kBlockHeight, kBlockRoundness, kBlockSegments), color(color), point(points) {
}

void Block :: Draw() {
	if (!disabled) {
		DrawRectangleRounded(get_rec(), get_roundness(), (int)get_segments(), color);
		if (falling) {
			DrawText(std::to_string(get_point()).c_str(), get_rec().x + get_rec().width/3, get_rec().y + 6, 20, ComplementaryColor(color));
		}
	}
}

void Block :: Move() {
	auto position = get_position();

	if (position.y > PlayingBarPosY(SCREEN_HEIGHT)) {
		set_disabled();
		++num_of_disabled_blocks;
	} else {
		position.y += kBlockFallingSpeed;
		set_position(position);
	}
}