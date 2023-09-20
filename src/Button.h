/*
 * Button.h
 *
 *  Created on: Sep. 19, 2023
 *      Author: Dong Won Kim
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <memory>
#include "EasyBreakout.h"
#include "GraphicsEntity.h"

enum button_state_t { normal, mouse_hover, pressed };

class Button : public GraphicsEntity {
private:
    const Texture2D * button = nullptr;
    const Sound * sound = nullptr;
    button_state_t state = normal;
    bool activated = false;
    Rectangle source_rectangle = (Rectangle){ 0, 0, (float)button->width, frame_height() };   

    const float frame_height() {
        return (float)button->height / kNumberOfFrames;
    } 

    const Rectangle btn_bounds() { 
        // return (Rectangle){ SCREEN_WIDTH/2.0f - button.width/2.0f, SCREEN_HEIGHT/2.0f - button.height/kNumberOfFrames/2.0f, (float)button.width, frame_height() };
        return (Rectangle){ this->get_position().x, this->get_position().y, (float)button->width, frame_height() };
    }   

public:
    constexpr static int kNumberOfFrames = 3;

	Button(const Texture2D * button) : GraphicsEntity((Vector2){SCREEN_WIDTH/2.0f - button->width/2.0f, SCREEN_HEIGHT/2.0f - button->height/kNumberOfFrames/2.0f}), button(button) { }
	Button(const Texture2D * button, const float& pos_x) : GraphicsEntity((Vector2){pos_x, SCREEN_HEIGHT/2.0f - button->height/kNumberOfFrames/2.0f}), button(button) { }	
    Button(const Texture2D * button, const Sound * sound, const float& pos_x) 
        : GraphicsEntity((Vector2){pos_x, SCREEN_HEIGHT/2.0f - button->height/kNumberOfFrames/2.0f}), sound(sound), button(button) { }
    Button(const Texture2D * button, const Sound * sound, const Vector2& position) : GraphicsEntity(position), sound(sound), button(button) { }
	virtual ~Button() { }

    const button_state_t& get_state() const & { return state; }
    button_state_t get_state() && { return std::move(state); }    
    const bool get_activated() const { return activated; } 

    void set_state(const button_state_t& state) { this->state = state; }
    void set_activated(const bool& activated) { this->activated = activated; }

    void check_click(const Vector2& mouse_point) {
        if (CheckCollisionPointRec(mouse_point, btn_bounds())) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) state = pressed;
            else state = mouse_hover;
            
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) activated = true;
        } else state = normal;

        if (activated && sound) PlaySound(*sound);

        // Calculate button frame rectangle to draw depending on button state
        source_rectangle.y = state * frame_height();     
    }

    void Draw() override {
        const Rectangle bounds = btn_bounds();
        DrawTextureRec(*button, source_rectangle, (Vector2){ bounds.x, bounds.y }, WHITE); // Draw button frame
    }
};

#endif // BUTTON_H_