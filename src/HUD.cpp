/*
 * HUD.cpp
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "HUD.h"

HUD::HUD()
{
    left_touch_point_.set_position((Vector2){100 * WindowManager::scale().x, WindowManager::window_size().height - WindowManager::window_size().height / 3.0f});
    right_touch_point_.set_position((Vector2){WindowManager::window_size().width - 100 * WindowManager::scale().x, WindowManager::window_size().height - WindowManager::window_size().height / 3.0f});
}

bool HUD::IsTouchPointTouched(const TouchPoint &tp) const
{
    const Vector2 position = tp.get_position();
    return GetTouchX() >= position.x - tp.get_shape().get_radius() && GetTouchX() <= position.x + tp.get_shape().get_radius() && GetTouchY() >= position.y - tp.get_shape().get_radius() && GetTouchY() <= position.y + tp.get_shape().get_radius() ? true : false;
}

void HUD::Draw()
{
    // Draw touch points
    left_touch_point_.Draw();
    right_touch_point_.Draw();
}