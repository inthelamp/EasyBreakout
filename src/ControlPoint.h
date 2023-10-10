/*
 * ControlPoint.h
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#ifndef CONTROL_POINT_H_
#define CONTROL_POINT_H_

#include "raylib.h"

#include "GraphicsEntity.h"
#include "Circle.h"

class ControlPoint : public GraphicsEntity<Circle>
{
public:
    constexpr static float kDefaultRadius = 34.0f; // Control point radius

    ControlPoint();
    ControlPoint(const Vector2 &position);
    ControlPoint(const Color &color, float radius, const Vector2 &position);

    void Draw() override;
    Circle Scale(Circle &&shape) override;

private:
    const static Color kDefaultColor;

    Color color;

    static Circle circle()
    {
        return std::move(Circle(kDefaultRadius));
    }

    static Circle circle(float radius)
    {
        return std::move(Circle(radius));
    }
};

#endif // CONTROL_POINT_H_