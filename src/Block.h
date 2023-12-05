/*
 * Block.h
 *
 *  Created on: Aug. 29, 2023
 *      Author: Dong Won Kim
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <iostream>

#include "raylib.h"

#include "WindowManager.h"
#include "MovingEntity.h"
#include "RoundedRect.h"

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

inline float block_roundness() { return 0.2f * WindowManager::scale().x; }

// Block falling speed on y-axis
inline float block_falling_speed() { return 5.0f * WindowManager::scale().y; }

class Block : public MovingEntity, public RoundedRect
{
public:
	Block();
	Block(const Color &color, int points, const Vector2 &position);

	const static float block_width() { return kBlockSize.width * WindowManager::scale().x; }
	const static float block_height() { return kBlockSize.height * WindowManager::scale().y; }

	const Color &get_color() const & { return color; }
	Color get_color() && { return std::move(color); }
	int get_point() { return point; }
	bool is_disabled() { return disabled; }
	bool is_falling() { return falling; }
	void set_disabled() { disabled = true; }
	void set_falling() { falling = true; }

	void Move() override;
	void Draw() override;

private:
	constexpr static Size kBlockSize = (Size){100, 30};
	constexpr static float kBlockSegments = 0.0f;

	Color color;
	int point;
	bool disabled = false;
	bool falling = false;

	static Rectangle rectangle(const Vector2 &position)
	{
		return (Rectangle){position.x * WindowManager::scale().x, position.y * WindowManager::scale().y, kBlockSize.width, kBlockSize.height};
	}
};

#endif // BLOCK_H