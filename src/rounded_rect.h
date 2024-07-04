/*
 * rounded_rect.h
 *
 *  Created on: Aug. 27, 2023
 *      Author: Dong Won Kim
 */

#ifndef ROUNDEDRECT_H_
#define ROUNDEDRECT_H_

#include <utility>

#include "raylib.h"

#include "screen.h"
#include "graphics_entity.h"

class RoundedRect : public GraphicsEntity<Rectangle>
{
public:
	RoundedRect(const Rectangle &rec, float pos_y, float roundness, float segments);
	RoundedRect(const Rectangle &rec, float roundness, float segments);

	float roundness() { return roundness_; }
	float segments() { return segments_; }

	Rectangle Scale(Rectangle &&shape) override;

private:
	float roundness_ = 0.2f;
	float segments_ = 0.0f;

	constexpr static Vector2 position(const Rectangle &rec, float pos_y)
	{
		return {Screen::window_size().width / 2 - rec.width / 2, pos_y};
	}
};

#endif // ROUNDEDRECT_H_
