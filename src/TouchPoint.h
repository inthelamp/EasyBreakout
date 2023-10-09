/*
 * TouchPoint.h
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#ifndef TOUCH_POINT_H_
#define TOUCH_POINT_H_

#include "raylib.h"
#include "GraphicsEntity.h"
#include "Circle.h"

class TouchPoint : public GraphicsEntity<Circle>
{
public:
    TouchPoint();
    TouchPoint(const Vector2 &position);

    void Draw() override;
    Circle Scale(Circle &&shape) override;

private:
    constexpr static float kRadius = 34.0f; // Touch point radius
    constexpr static Color color = ORANGE;

    static Circle circle()
    {
        return std::move(Circle(kRadius));
    }
};

#endif // TOUCH_POINT_H_