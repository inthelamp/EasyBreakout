/*
 * GraphicsEntity.h
 *
 *  Created on: Aug. 28, 2023
 *      Author: Dong Won Kim
 */

#ifndef GRAPHICSENTITY_H_
#define GRAPHICSENTITY_H_

#include <utility>
#include <typeinfo>

#include "raylib.h"

#include "WindowManager.h"
#include "Circle.h"

template <typename T>
class GraphicsEntity
{
public:
	GraphicsEntity(const T &shape, const Vector2 &position);
	virtual ~GraphicsEntity(){};

	const T &get_shape() const & { return shape; }
	T get_shape() && { return std::move(shape); }
	void set_shape(const T &shape) { this->shape = shape; }
	void set_shape(T &&shape) { this->shape = std::move(shape); }

	const Vector2 &get_position() const { return position; }
	float get_position_x() { return position.x; }
	void set_position(const Vector2 &position);
	void set_position(Vector2 &&position);
	void set_position_x(float x);
	void set_position_y(float y);

	virtual T Scale(T &&shape) = 0; // Adjust scale of game object
	virtual void Draw() = 0;		// Display game object

private:
	T shape;
	Vector2 position;
};

#endif // GRAPHICSENTITY_H_
