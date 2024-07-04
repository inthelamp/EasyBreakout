/*
 * hud.cc
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "hud.h"

bool HUD::IsControlPointTouched(ControlPoint *tp)
{
    const Vector2 position = tp->position();
    return GetTouchX() >= position.x - tp->shape().radius() && GetTouchX() <= position.x + tp->shape().radius() && GetTouchY() >= position.y - tp->shape().radius() && GetTouchY() <= position.y + tp->shape().radius() ? true : false;
}

void HUD::Draw()
{
    // Draw control points
    hit_back_control_->Draw();
    left_control_->Draw();
    right_control_->Draw();
}