/*
 * screen.cc
 *
 *  Created on: Sept. 26, 2023
 *      Author: Dong Won Kim
 */

#include "screen.h"

// Screen size
#if defined(EMSCRIPTEN)
const int Screen::kWidth = Screen::web_window_size().width;
const int Screen::kHeight = Screen::web_window_size().height;
#else
const int Screen::kWidth = kMaxWidth;
const int Screen::kHeight = kMaxHeight;
const Vector2 Screen::kScale = {1.0f, 1.0f};
#endif

void Screen::DisplayText(const DisplayArea &display_area, const char *text, int pos_x, int pos_y, int font_size, const Color &color)
{

	// Apply scale
	const int scaled_pos_x = pos_x * Screen::scale().x;
	const int scaled_pos_y = pos_y * Screen::scale().y;

	switch (display_area)
	{
	case kLeft:
		DrawText(text, scaled_pos_x, scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	case kMiddle:
		DrawText(text, Screen::window_size().width / 2 + scaled_pos_x, scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	case kRight:
		DrawText(text, Screen::window_size().width + scaled_pos_x, scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	case kCentre:
		DrawText(text, Screen::window_size().width / 2 + scaled_pos_x, Screen::window_size().height / 2 + scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	case kBottomLeft:
		DrawText(text, scaled_pos_x, Screen::window_size().height + scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	case kBottomMiddle:
		DrawText(text, Screen::window_size().width / 2 + scaled_pos_x, Screen::window_size().height + scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	case kBottomRight:
		DrawText(text, Screen::window_size().width + scaled_pos_x, Screen::window_size().height + scaled_pos_y, font_size * Screen::scale().x, color);
		break;
	default:
		DrawText(text, pos_x, pos_y, font_size * Screen::scale().x, color);
		break;
	}
}