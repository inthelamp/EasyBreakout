/*
 * HUD.cpp
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "HUD.h"

bool HUD::IsControlPointTouched(const ControlPoint &tp) const
{
    const Vector2 position = tp.get_position();
    return GetTouchX() >= position.x - tp.get_shape().get_radius() && GetTouchX() <= position.x + tp.get_shape().get_radius() && GetTouchY() >= position.y - tp.get_shape().get_radius() && GetTouchY() <= position.y + tp.get_shape().get_radius() ? true : false;
}

void HUD::Draw()
{
    // Draw control points
    hit_back_control_.Draw();
    left_control_.Draw();
    right_control_.Draw();
}