/*
 * button.cc
 *
 *  Created on: Sep. 26, 2023
 *      Author: Dong Won Kim
 */

#include "button.h"

Button::Button(const Texture2D &texture, const Sound &sound, float pos_x) : GraphicsEntity<Rectangle>(rectangle((float)texture.width, frame_height(texture), pos_x), position(frame_height(texture), pos_x)), texture_(texture), sound_(sound), source_rectangle_((Rectangle){0, 0, (float)texture.width, frame_height(texture)})
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

Button::Button(const Texture2D &texture, const Sound &sound, const Rectangle &source_rec, const Vector2 &position) : GraphicsEntity<Rectangle>(rectangle((float)texture.width, frame_height(texture), position), position), texture_(texture), sound_(sound), source_rectangle_(source_rec)
{
    auto shape = GraphicsEntity::shape();
    GraphicsEntity::shape(Scale(std::move(shape)));
}

Rectangle Button::Scale(Rectangle &&shape)
{
    shape.width = shape.width * Screen::scale().x;
    shape.height = shape.height * Screen::scale().x;
    return std::move(shape);
}

void Button::CheckClick(const Vector2 &mouse_point)
{
    if (CheckCollisionPointRec(mouse_point, shape()))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            state(kPressed);
        else
            state(kMouseHover);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            activated(true);
    }
    else
        state(kNormal);

    if (activated())
        PlaySound(sound_);

    // Calculate button frame rectangle to draw depending on button state
    source_rectangle_.y = state() * (int)frame_height(texture_);
}

void Button::Draw()
{
    constexpr float rotation = 0.0f;
    DrawTexturePro(texture_, source_rectangle_, shape(), {0.0f, 0.0f}, rotation, WHITE);
}