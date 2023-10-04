/*
 * RoundedRect.h
 *
 *  Created on: Aug. 27, 2023
 *      Author: Dong Won Kim
 */

#ifndef ROUNDEDRECT_H_
#define ROUNDEDRECT_H_

#include <utility>

#include "raylib.h"

#include "WindowManager.h"
#include "GraphicsEntity.h"

class RoundedRect : public GraphicsEntity<Rectangle>
{
public:
	RoundedRect(const Rectangle &rec, float pos_y, float roundness, float segments);
	RoundedRect(const Rectangle &rec, float roundness, float segments);
	virtual ~RoundedRect(){};

	float get_roundness() { return roundness; }
	float get_segments() { return segments; }

	Rectangle Scale(Rectangle &&shape) override;

private:
	float roundness = 0.2f;
	float segments = 0.0f;

	static Vector2 position(const Rectangle &rec, float pos_y)
	{
		return (Vector2){WindowManager::window_width() / 2 - rec.width / 2, pos_y};
	}
};

#endif // ROUNDEDRECT_H_
