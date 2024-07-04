/*
 * control_point.h
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#ifndef CONTROL_POINT_H_
#define CONTROL_POINT_H_

#include "raylib.h"

#include "graphics_entity.h"
#include "tutorial_condition.h"
#include "circle.h"

class ControlPoint : public TutorialCondition, public GraphicsEntity<Circle>
{
public:
    constexpr static float kDefaultRadius = 34.0f; // Control point radius

    ControlPoint();
    ControlPoint(const Vector2 &position);
    ControlPoint(const Color &color, float radius, const Vector2 &position);

    void Draw() override;
    Circle Scale(Circle &&shape) override;

private:
    static const Color kDefaultColor;
    // Get a circle with default radius
    static Circle circle()
    {
        return std::move(Circle(kDefaultRadius));
    }
    // Get a circle with given radius
    static Circle circle(float radius)
    {
        return std::move(Circle(radius));
    }

    Color color_;
};

#endif // CONTROL_POINT_H_