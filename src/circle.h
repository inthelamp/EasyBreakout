/*
 * circle.h
 *
 *  Created on: Aug. 24, 2023
 *      Author: Dong Won Kim
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

class Circle
{
public:
	Circle(int radius) : radius_(radius) {}
	Circle(const Circle &) = default;			 // Copy constructor
	Circle(Circle &&) = default;				 // Move constructor
	Circle &operator=(const Circle &) = default; // Copy assignment operator
	Circle &operator=(Circle &&) = default;		 // Move assignment operator
	virtual ~Circle() = default;

	const int &radius() const { return radius_; }
	void radius(int radius) { radius_ = radius; }

private:
	int radius_;
};

#endif // CIRCLE_H_