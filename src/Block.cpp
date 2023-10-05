/*
 * Block.cpp
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#include "Block.h"

Block::Block() : MovingEntity({0.0f, block_falling_speed()}), RoundedRect((Rectangle){0.0f, 0.0f, kBlockSize.width, kBlockSize.height}, block_roundness(), kBlockSegments), color(random_color()), point(random_points())
{
}

Block::Block(const Color &color, int points, const Vector2 &position) : MovingEntity({0.0f, block_falling_speed()}), RoundedRect(rectangle(position), block_roundness(), kBlockSegments), color(color), point(points)
{
}

void Block::Draw()
{
	if (!disabled)
	{
		DrawRectangleRounded(this->get_shape(), get_roundness(), (int)get_segments(), color);
		if (falling)
		{
			WindowManager::DisplayText(kAnywhere, std::to_string(get_point()).c_str(), this->get_position_x() + this->get_shape().width / 3, this->get_shape().y + 6, 20, complementary_color(color));
		}
	}
}

void Block::Move()
{
	auto position = get_position();

	if (position.y < WindowManager::window_size().height)
	{
		position.y += block_falling_speed();
		set_position(position);
	}
}