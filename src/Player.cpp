/*
 * Player.cpp
 *
 *  Created on: Sep. 7, 2023
 *      Author: Dong Won Kim
 */

#include "Player.h"
#include "Level.h"

Player :: Player(const Level * level) : level(level), score(0) {
}