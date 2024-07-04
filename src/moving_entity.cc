/*
 * moving_entity.cc
 *
 *  Created on: Sept. 30, 2023
 *      Author: Dong Won Kim
 */

#include "moving_entity.h"

const float MovingEntity::kSpeedIncrementRate = 0.2f * Screen::scale().x;

MovingEntity::MovingEntity(const Vector2 &speed) : speed_(speed) {}