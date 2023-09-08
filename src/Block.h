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

class Block : public MovingEntity, public RoundedRect {
private:
	const Color color;
	const int point;

	bool disabled = false; 
	bool falling = false;

	constexpr static float kBlockRoundness = 0.2f;
	constexpr static float kBlockSegments = 0.0f;

public:
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