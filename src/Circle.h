/*
 * Circle.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <utility>

class Circle
{
public:
	Circle(int radius) : radius(radius) {}
	virtual ~Circle() {}

	const int &get_radius() const { return radius; }
	void set_radius(int radius) { this->radius = radius; }

private:
	int radius;
};

#endif // CIRCLE_H_