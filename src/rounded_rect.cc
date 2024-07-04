/*
 * rounded_rect.cc
 *
 *  Created on: Sept. 28, 2023
 *      Author: Dong Won Kim
 */

#include "rounded_rect.h"

RoundedRect::RoundedRect(const Rectangle &rec, float pos_y, float roundness, float segments) : GraphicsEntity<Rectangle>(rec, position(rec, pos_y)), roundness_(roundness), segments_(segments)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

RoundedRect::RoundedRect(const Rectangle &rec, float roundness, float segments) : GraphicsEntity<Rectangle>(rec, {rec.x, rec.y}), roundness_(roundness), segments_(segments)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

Rectangle RoundedRect::Scale(Rectangle &&shape)
{
    shape.width = shape.width * Screen::scale().x;
    shape.height = shape.height * Screen::scale().x;
    return std::move(shape);
}