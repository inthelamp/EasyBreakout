/*
 * WindowManager.cpp
 *
 *  Created on: Sept. 26, 2023
 *      Author: Dong Won Kim
 */

#include "WindowManager.h"

// Screen size
#if defined(EMSCRIPTEN)
const int WindowManager::kWindowWidth = WindowManager::web_window_size().width;
const int WindowManager::kWindowHeight = WindowManager::web_window_size().height;
#else
const int WindowManager::kWindowWidth = kWindowMaxWidth;
const int WindowManager::kWindowHeight = kWindowMaxHeight;
const Vector2 WindowManager::kScale = (Vector2){1.0f, 1.0f};
#endif

void WindowManager::DisplayText(const DisplayArea &display_area, const char *text, int pos_x, int pos_y, int font_size, const Color &color)
{

	// Apply scale
	const int scaled_pos_x = pos_x * WindowManager::scale().x;
	const int scaled_pos_y = pos_y * WindowManager::scale().y;

	switch (display_area)
	{
	case kLeft:
		DrawText(text, scaled_pos_x, scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	case kMiddle:
		DrawText(text, WindowManager::window_size().width / 2 + scaled_pos_x, scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	case kRight:
		DrawText(text, WindowManager::window_size().width + scaled_pos_x, scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	case kCentre:
		DrawText(text, WindowManager::window_size().width / 2 + scaled_pos_x, WindowManager::window_size().height / 2 + scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	case kBottomLeft:
		DrawText(text, scaled_pos_x, WindowManager::window_size().height + scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	case kBottomMiddle:
		DrawText(text, WindowManager::window_size().width / 2 + scaled_pos_x, WindowManager::window_size().height + scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	case kBottomRight:
		DrawText(text, WindowManager::window_size().width + scaled_pos_x, WindowManager::window_size().height + scaled_pos_y, font_size * WindowManager::scale().x, color);
		break;
	default:
		DrawText(text, pos_x, pos_y, font_size * WindowManager::scale().x, color);
		break;
	}
}