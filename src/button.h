/*
 * button.h
 *
 *  Created on: Sep. 19, 2023
 *      Author: Dong Won Kim
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "raylib.h"

#include "screen.h"
#include "graphics_entity.h"
#include "clickable.h"

class Button : public Clickable, public GraphicsEntity<Rectangle>
{
public:
    Button(const Texture2D &texture, const Sound &sound, float pos_x);
    Button(const Texture2D &texture, const Sound &sound, const Rectangle &source_rec, const Vector2 &position);

    const Texture2D &texture() const { return texture_; }
    const Sound &sound() const & { return sound_; }

    void CheckClick(const Vector2 &mouse_point) override;
    Rectangle Scale(Rectangle &&shape) override;
    void Draw() override;

private:
    constexpr static int kNumberOfFrames = 3;
    // Get hight of frame from texture
    constexpr static float frame_height(const Texture2D &texture)
    {
        return (float)texture.height / kNumberOfFrames;
    }
    // Get a rectangle
    static Rectangle rectangle(float width, float height, float pos_x)
    {
        return {Screen::window_size().width / 2 + pos_x * Screen::scale().x, Screen::window_size().height / 2 - height / 2, width, height};
    }
    // Get a rectangle
    constexpr static Rectangle rectangle(float width, float height, const Vector2 &position)
    {
        return {position.x, position.y, width, height};
    }
    // Get a position
    static Vector2 position(float height, float pos_x)
    {
        return {Screen::window_size().width / 2 + pos_x * Screen::scale().x, Screen::window_size().height / 2 - height / 2};
    }

    Texture2D texture_;
    Sound sound_;
    Rectangle source_rectangle_;
};

#endif // BUTTON_H_