/*
 * TouchPoint.cpp
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "TouchPoint.h"

TouchPoint::TouchPoint() : GraphicsEntity<Circle>(circle(), (Vector2){0.0f, 0.0f})
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

TouchPoint::TouchPoint(const Vector2 &position) : GraphicsEntity<Circle>(circle(), position)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

Circle TouchPoint::Scale(Circle &&circle)
{
    circle.set_radius(circle.get_radius() * WindowManager::scale().x);
    return std::move(circle);
}

void TouchPoint::Draw()
{
    DrawCircleV(get_position(), kRadius, color);
}