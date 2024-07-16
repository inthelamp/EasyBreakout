/*
 * hud.cc
 *
 *  Created on: Oct. 07, 2023
 *      Author: Dong Won Kim
 */

#include "hud.h"

void HUD::Draw()
{
    // Draw control points
    hit_back_control_->Draw();
    left_control_->Draw();
    right_control_->Draw();
}