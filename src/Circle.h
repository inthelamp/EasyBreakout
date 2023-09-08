/*
 * Circle.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <utility>
#include "raylib.h"
#include "GraphicsEntity.h"

class Circle : public GraphicsEntity {
private:
	int radius;

public:
	Circle(const Vector2& position, const int& radius) : GraphicsEntity(position) { this->radius = radius; }
	virtual ~Circle() { }

	const int& get_radius() const & { return radius; }
	int get_radius() && { return std::move(radius); }
	void set_radius(const int& radius) { this->radius = radius; }
};

#endif // CIRCLE_H_ 
