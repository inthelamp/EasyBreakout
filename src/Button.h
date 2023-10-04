/*
 * Button.h
 *
 *  Created on: Sep. 19, 2023
 *      Author: Dong Won Kim
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "raylib.h"

#include "WindowManager.h"
#include "GraphicsEntity.h"

enum ButtonState
{
    kNormal,
    kMouseHover,
    kPressed
};

class Button : public GraphicsEntity<Rectangle>
{
public:
    Button(const Texture2D &button, float pos_x);
    Button(const Texture2D &button, const Sound *const sound, float pos_x);
    Button(const Texture2D &button, const Sound *const sound, const Rectangle &source_rec, const Vector2 &position);
    virtual ~Button() {}

    ButtonState get_state() { return state; }
    void set_state(ButtonState state) { this->state = state; }
    bool is_activated() { return activated; }
    void set_activated(bool activated) { this->activated = activated; }

    void check_click(const Vector2 &mouse_point);
    Rectangle Scale(Rectangle &&shape) override;
    void Draw() override;

private:
    constexpr static int kNumberOfFrames = 3;

    Texture2D button;
    const Sound *const sound{nullptr};
    Rectangle source_rectangle;

    ButtonState state = kNormal;
    bool activated = false;

    static float frame_height(const Texture2D &button)
    {
        return (float)button.height / kNumberOfFrames;
    }

    static Rectangle rectangle(float width, float height, float pos_x)
    {
        return (Rectangle){WindowManager::window_width() / 2 + pos_x * WindowManager::scale().x, WindowManager::window_height() / 2 - height / 2, width, height};
    }

    static Rectangle rectangle(float width, float height, const Vector2 &position)
    {
        return (Rectangle){position.x, position.y, width, height};
    }

    static Vector2 position(float height, float pos_x)
    {
        return (Vector2){WindowManager::window_width() / 2 + pos_x * WindowManager::scale().x, WindowManager::window_height() / 2 - height / 2};
    }
};

#endif // BUTTON_H_