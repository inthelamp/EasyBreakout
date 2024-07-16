/*
 * graphics_entity.cc
 *
 *  Created on: Sept. 28, 2023
 *      Author: Dong Won Kim
 */
#include "graphics_entity.h"

#if !defined(EMSCRIPTEN)
template class GraphicsEntity<Circle>;
template class GraphicsEntity<Rectangle>;

template <typename T>
GraphicsEntity<T>::GraphicsEntity(const T &shape, const Vector2 &position) : shape_(shape), position_(position) {}
template <typename T>
GraphicsEntity<T>::GraphicsEntity(const T &shape, const Vector2 &position, bool displayed) : shape_(shape), position_(position), displayed_(displayed) {}
#endif

#if defined(EMSCRIPTEN)
template <>
GraphicsEntity<Circle>::GraphicsEntity(const Circle &shape, const Vector2 &position) : shape_(shape), position_(position) {}

template <>
GraphicsEntity<Circle>::GraphicsEntity(const Circle &shape, const Vector2 &position, bool displayed) : shape_(shape), position_(position), displayed_(displayed) {}

template <>
GraphicsEntity<Rectangle>::GraphicsEntity(const Rectangle &shape, const Vector2 &position) : shape_(shape), position_(position) {}

template <>
GraphicsEntity<Rectangle>::GraphicsEntity(const Rectangle &shape, const Vector2 &position, bool displayed) : shape_(shape), position_(position), displayed_(displayed) {}
#endif

template <>
void GraphicsEntity<Rectangle>::position(const Vector2 &position)
{
    shape_.x = position.x;
    shape_.y = position.y;

    position_ = position;
}

template <>
void GraphicsEntity<Circle>::position(const Vector2 &position)
{
    position_ = position;
}

template <>
void GraphicsEntity<Rectangle>::position(Vector2 &&position)
{
    shape_.x = position.x;
    shape_.y = position.y;
    position_ = std::move(position);
}

template <>
void GraphicsEntity<Circle>::position(Vector2 &&position)
{
    position_ = std::move(position);
}

template <>
void GraphicsEntity<Rectangle>::position_x(float x)
{
    shape_.x = x;
    position_.x = x;
}

template <>
void GraphicsEntity<Circle>::position_x(float x)
{
    position_.x = x;
}

template <>
void GraphicsEntity<Rectangle>::position_y(float y)
{
    shape_.y = y;
    position_.y = y;
}

template <>
void GraphicsEntity<Circle>::position_y(float y)
{
    position_.y = y;
}