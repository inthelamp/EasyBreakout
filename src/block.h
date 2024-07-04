/*
 * block.h
 *
 *  Created on: Aug. 29, 2023
 *      Author: Dong Won Kim
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <iostream>

#include "raylib.h"

#include "screen.h"
#include "moving_entity.h"
#include "rounded_rect.h"

// Getting random color
inline Color random_color()
{
	return (Color){(unsigned char)GetRandomValue(0, 254), (unsigned char)GetRandomValue(0, 254), (unsigned char)GetRandomValue(0, 254), 0xff};
}

// Getting random points
inline int random_points()
{
	return GetRandomValue(50, 200);
}

// Getting complementary color
inline constexpr Color complementary_color(const Color &color)
{
	return {static_cast<unsigned char>(255 - (int)color.r), static_cast<unsigned char>(255 - (int)color.g), static_cast<unsigned char>(255 - (int)color.b), 0xff};
}

inline float block_roundness() { return 0.2f * Screen::scale().x; }

// Block falling speed on y-axis
inline float block_falling_speed() { return 5.0f * Screen::scale().y; }

class Block : public MovingEntity, public RoundedRect
{
public:
	static const float block_width() { return kBlockSize.width * Screen::scale().x; }
	static const float block_height() { return kBlockSize.height * Screen::scale().y; }

	Block();
	Block(const Color &color, int points, const Vector2 &position);
	Block(const Block &) = delete;		 // Copy constructor
	Block(Block &&) = delete;			 // Move constructor
	Block &operator=(const Block &);	 // Copy assignment operator
	Block &operator=(Block &&) = delete; // Move assignment operator
	~Block() = default;

	const Color &color() const & { return color_; }
	Color color() && { return std::move(color_); }
	int score() { return score_; }
	bool disabled() { return disabled_; }
	bool falling() { return falling_; }
	void disabled(bool disabled) { disabled_ = disabled; }
	void falling(bool falling) { falling_ = falling; }

	void Move() override;
	void Draw() override;

private:
	constexpr static Size kBlockSize = (Size){100, 30};
	constexpr static float kBlockSegments = 0.0f;
	static Rectangle rectangle(const Vector2 &position)
	{
		return {position.x * Screen::scale().x, position.y * Screen::scale().y, kBlockSize.width, kBlockSize.height};
	}

	Color color_;
	int score_;
	bool disabled_ = false;
	bool falling_ = false;
};

#endif // BLOCK_H