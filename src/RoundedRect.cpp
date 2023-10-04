/*
 * RoundedRect.cpp
 *
 *  Created on: Sept. 28, 2023
 *      Author: Dong Won Kim
 */

#include "RoundedRect.h"

RoundedRect::RoundedRect(const Rectangle &rec, float pos_y, float roundness, float segments) : GraphicsEntity<Rectangle>(rec, position(rec, pos_y)), roundness(roundness), segments(segments)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

RoundedRect::RoundedRect(const Rectangle &rec, float roundness, float segments) : GraphicsEntity<Rectangle>(rec, (Vector2){rec.x, rec.y}), roundness(roundness), segments(segments)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

Rectangle RoundedRect::Scale(Rectangle &&shape)
{
    shape.width = shape.width * WindowManager::scale().x;
    shape.height = shape.height * WindowManager::scale().x;
    return std::move(shape);
}