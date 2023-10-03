/*
 * EasyBreakout.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#ifndef EASY_BREAKOUT_
#define EASY_BREAKOUT_

// #define PLATFORM_WEB
#if defined(EMSCRIPTEN)
#include <emscripten/emscripten.h>
#endif

#include "raylib.h"

#include "WindowManager.h"
#include "MovingEntity.h"
#include "Button.h"
#include "Level.h"
#include "Block.h"
#include "PlayingBar.h"
#include "Ball.h"
#include "Player.h"
#include "StorageValue.h"

constexpr Color kBackgroundColor = RAYWHITE; // Background color

// Audio definition
constexpr float kBackgroundSoundVolumn = 0.2f; // Background sound volumn, 1.0 is maximum

#endif // EASY_BREAKOUT_