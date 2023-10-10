/*
 * Button.cpp
 *
 *  Created on: Sep. 26, 2023
 *      Author: Dong Won Kim
 */

#include "Button.h"

Button::Button(const Texture2D &button, float pos_x) : GraphicsEntity<Rectangle>(rectangle((float)button.width, frame_height(button), pos_x), position(frame_height(button), pos_x)), button(button), source_rectangle((Rectangle){0, 0, (float)button.width, frame_height(button)})
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

Button::Button(const Texture2D &button, const Sound *const sound, float pos_x) : GraphicsEntity<Rectangle>(rectangle((float)button.width, frame_height(button), pos_x), position(frame_height(button), pos_x)), button(button), sound(sound), source_rectangle((Rectangle){0, 0, (float)button.width, frame_height(button)})
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

Button::Button(const Texture2D &button, const Sound *const sound, const Rectangle &source_rec, const Vector2 &position) : GraphicsEntity<Rectangle>(rectangle((float)button.width, frame_height(button), position), position), button(button), sound(sound), source_rectangle(source_rec)
{
    auto shape = get_shape();
    set_shape(Scale(std::move(shape)));
}

Rectangle Button::Scale(Rectangle &&shape)
{
    shape.width = shape.width * WindowManager::scale().x;
    shape.height = shape.height * WindowManager::scale().x;
    return std::move(shape);
}

void Button::check_click(const Vector2 &mouse_point)
{
    if (CheckCollisionPointRec(mouse_point, get_shape()))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            state = kPressed;
        else
            state = kMouseHover;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            activated = true;
    }
    else
        state = kNormal;

    if (activated && sound)
        PlaySound(*sound);

    // Calculate button frame rectangle to draw depending on button state
    source_rectangle.y = state * (int)frame_height(button);
}

void Button::Draw()
{
    constexpr float rotation = 0.0f;
    DrawTexturePro(button, source_rectangle, get_shape(), (Vector2){0.0f, 0.0f}, rotation, WHITE);
}