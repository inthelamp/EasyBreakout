/*
 * ControlPoint.cpp
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "ControlPoint.h"

const Color ControlPoint::kDefaultColor = Fade(ORANGE, 0.1f);

ControlPoint::ControlPoint() : GraphicsEntity<Circle>(circle(), (Vector2){0.0f, 0.0f}), color(kDefaultColor)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

ControlPoint::ControlPoint(const Vector2 &position) : GraphicsEntity<Circle>(circle(), position), color(kDefaultColor)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

ControlPoint::ControlPoint(const Color &color, float radius, const Vector2 &position) : GraphicsEntity<Circle>(circle(radius), position), color(color)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

Circle ControlPoint::Scale(Circle &&circle)
{
    circle.set_radius(circle.get_radius() * WindowManager::scale().x);
    return std::move(circle);
}

void ControlPoint::Draw()
{
    DrawCircleV(get_position(), this->get_shape().get_radius(), color);
}