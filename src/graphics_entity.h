/*
 * graphics_entity.h
 *
 *  Created on: Aug. 28, 2023
 *      Author: Dong Won Kim
 */

#ifndef GRAPHICS_ENTITY_H_
#define GRAPHICS_ENTITY_H_

#include <utility>
#include <typeinfo>

#include "raylib.h"

#include "screen.h"
#include "circle.h"

template <typename T>
class GraphicsEntity
{
public:
	GraphicsEntity(const T &shape, const Vector2 &position);
	GraphicsEntity(const T &shape, const Vector2 &position, bool displayed);
	GraphicsEntity(const GraphicsEntity &) = delete;			// Copy constructor
	GraphicsEntity(GraphicsEntity &&) = delete;					// Move constructor
	GraphicsEntity &operator=(const GraphicsEntity &) = delete; // Copy assignment operator
	GraphicsEntity &operator=(GraphicsEntity &&) = delete;		// Move assignment operator
	virtual ~GraphicsEntity() = default;

	const T &shape() const & { return shape_; }
	T shape() && { return std::move(shape_); }
	void shape(const T &shape) { shape_ = shape; }
	void shape(T &&shape) { shape_ = std::move(shape); }

	const Vector2 &position() const & { return position_; }
	Vector2 position() && { return std::move(position_); }

	float position_x() { return position_.x; }
	float position_y() { return position_.y; }
	void position(const Vector2 &position);
	void position(Vector2 &&position);
	void position_x(float x);
	void position_y(float y);
	bool displayed() { return displayed_; }
	void displayed(bool displayed) { displayed_ = displayed; }

	virtual T Scale(T &&shape) = 0; // Adjust scale of game object
	virtual void Draw() = 0;		// Display game object

private:
	T shape_;
	Vector2 position_;
	bool displayed_ = true;
};

#endif // GRAPHICS_ENTITY_H_
