/*
 * control_point.cc
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "control_point.h"

const Color ControlPoint::kDefaultColor = Fade(ORANGE, 0.1f);

ControlPoint::ControlPoint() : GraphicsEntity<Circle>(circle(), {0.0f, 0.0f}), color_(kDefaultColor)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

ControlPoint::ControlPoint(const Vector2 &position) : GraphicsEntity<Circle>(circle(), position), color_(kDefaultColor)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

ControlPoint::ControlPoint(const Vector2 &position, bool displayed) : GraphicsEntity<Circle>(circle(), position, displayed), color_(kDefaultColor)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

ControlPoint::ControlPoint(const Color &color, float radius, const Vector2 &position) : GraphicsEntity<Circle>(circle(radius), position), color_(color)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

bool ControlPoint::IsTouched()
{
    return GetTouchX() >= position_x() - shape().radius() && GetTouchX() <= position_x() + shape().radius() && GetTouchY() >= position_y() - shape().radius() && GetTouchY() <= position_y() + shape().radius() ? true : false;
}

Circle ControlPoint::Scale(Circle &&circle)
{
    circle.radius(circle.radius() * Screen::scale().x);
    return std::move(circle);
}

void ControlPoint::Draw()
{
    if (displayed())
    {
        DrawCircleV(GraphicsEntity::position(), shape().radius(), color_);
    }
}