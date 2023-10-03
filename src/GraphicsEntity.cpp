/*
 * GraphicsEntity.cpp
 *
 *  Created on: Sept. 28, 2023
 *      Author: Dong Won Kim
 */
#include "GraphicsEntity.h"

#if !defined(EMSCRIPTEN)
template class GraphicsEntity<Circle>;
template class GraphicsEntity<Rectangle>;

template <typename T>
GraphicsEntity<T>::GraphicsEntity(const T &shape, const Vector2 &position) : shape(shape), position(position) {}
#endif

#if defined(EMSCRIPTEN)
template <>
GraphicsEntity<Circle>::GraphicsEntity(const Circle &shape, const Vector2 &position) : shape(shape), position(position) {}

template <>
GraphicsEntity<Rectangle>::GraphicsEntity(const Rectangle &shape, const Vector2 &position) : shape(shape), position(position) {}
#endif

template <>
void GraphicsEntity<Rectangle>::set_position(const Vector2 &position)
{
    shape.x = position.x;
    shape.y = position.y;

    this->position = position;
}

template <>
void GraphicsEntity<Circle>::set_position(const Vector2 &position)
{
    this->position = position;
}

template <>
void GraphicsEntity<Rectangle>::set_position(Vector2 &&position)
{
    shape.x = position.x;
    shape.y = position.y;
    this->position = std::move(position);
}

template <>
void GraphicsEntity<Circle>::set_position(Vector2 &&position)
{
    this->position = std::move(position);
}

template <>
void GraphicsEntity<Rectangle>::set_position_x(float &&x)
{
    shape.x = x;
    position.x = std::move(x);
}

template <>
void GraphicsEntity<Circle>::set_position_x(float &&x)
{
    position.x = std::move(x);
}

template <>
void GraphicsEntity<Rectangle>::set_position_y(float &&y)
{
    shape.y = y;
    position.y = std::move(y);
}

template <>
void GraphicsEntity<Circle>::set_position_y(float &&y)
{
    position.y = std::move(y);
}