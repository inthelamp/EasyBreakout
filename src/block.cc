/*
 * block.cc
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include "block.h"

Block::Block() : MovingEntity({0.0f, block_falling_speed()}), RoundedRect((Rectangle){0.0f, 0.0f, kBlockSize.width, kBlockSize.height}, block_roundness(), kBlockSegments), color_(random_color()), score_(random_points())
{
}

Block::Block(const Color &color, int points, const Vector2 &position) : MovingEntity({0.0f, block_falling_speed()}), RoundedRect(rectangle(position), block_roundness(), kBlockSegments), color_(color), score_(points)
{
}

Block &Block::operator=(const Block &that)
{
	color_ = that.color_;
	score_ = that.score_;
	disabled_ = that.disabled_;
	falling_ = that.falling_;
	return *this;
}

void Block::Draw()
{
	if (!disabled_)
	{
		DrawRectangleRounded(shape(), roundness(), (int)segments(), color_);
		if (falling_)
		{
			Screen::DisplayText(kAnywhere, std::to_string(score()).c_str(), position_x() + shape().width / 3, shape().y + 6, 20, complementary_color(color_));
		}
	}
}

void Block::Move()
{
	auto position = GraphicsEntity::position();

	if (position.y < Screen::window_size().height)
	{
		position.y += block_falling_speed();
		GraphicsEntity::position(position);
	}
}