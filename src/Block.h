/*
 * Block.h
 *
 *  Created on: Aug. 29, 2023
 *      Author: Dong Won Kim
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <utility>
#include "raylib.h"
#include "MovingEntity.h"
#include "RoundedRect.h"

// Getting random color
inline Color RandomColor() {
	return (Color){ (unsigned char) GetRandomValue(0, 254), (unsigned char) GetRandomValue(0, 254), (unsigned char) GetRandomValue(0, 254), 0xff };
}

// Getting random points
inline int RandomPoints() {
	return GetRandomValue(50, 200);
}

// Getting complementary color
inline constexpr Color ComplementaryColor (const Color& color)
{
    return {static_cast<unsigned char>(255 - (int)color.r), static_cast<unsigned char>(255 - (int)color.g), static_cast<unsigned char>(255 - (int)color.b), 0xff};
}

class Block : public MovingEntity, public RoundedRect {
private:
	constexpr static float kBlockFallingSpeed = 5.0f;         // Block falling speed on y-axis
	constexpr static float kBlockRoundness = 0.2f;
	constexpr static float kBlockSegments = 0.0f;
	
	const Color color;
	const int point;

	bool disabled = false; 
	bool falling = false;
	
public:
	static int num_of_disabled_blocks;                        // Number of disabled blocks
	constexpr static float kBlockWidth = 100.0f;
	constexpr static float kBlockHeight = 30.0f;
	constexpr static float kBlockRowOffset = 1.0f;
	constexpr static float kBlockColumnOffset = 1.0f;

	Block();
	Block(const Color& color, const int& points, const Vector2& position);
	virtual ~Block() { }
	
	const Color& get_color() const & { return color; }
	Color get_color() && { return std::move(color); }
	const int& get_point() const { return point; }

	const bool is_disabled() const { return disabled; }
	const bool is_falling() const { return falling; }
	void set_disabled() { disabled = true; }
	void set_falling() { falling = true; }

	void Move() override;
    void Draw() override;
};

#endif // BLOCK_H 