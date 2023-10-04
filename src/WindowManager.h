/*
 * WindowManager.h
 *
 *  Created on: Sept. 26, 2023
 *      Author: Dong Won Kim
 */

#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#if defined(EMSCRIPTEN)
#include <emscripten/emscripten.h>
#endif

#include "raylib.h"

// NOTE: Display area
enum DisplayArea
{
	kLeft,
	kMiddle,		 // Position x is fixed, but position y is variable
	kVerticalMiddle, // In the middle of each vertical line, so position x is variable, but position y is fixed
	kRight,
	kCentre,
	kBottomLeft,
	kBottomMiddle,
	kBottomRight,
	kAnywhere
};

// Static class
class WindowManager
{
public:
	WindowManager() = delete;

	constexpr static int kWindowMinWidth = 480;	 // Minimum window width
	constexpr static int kWindowMinHeight = 270; // Minimum window height

// For Webassembly
#if defined(EMSCRIPTEN)
	static const Vector2 scale() { return (Vector2){kWindowWidth / 960.0f, kWindowHeight / 540.0f}; }
#else
	static const Vector2 scale() { return kScale; }
#endif
	static const int window_width() { return kWindowWidth; }
	static const int window_height() { return kWindowHeight; }
	static void DisplayText(const DisplayArea &display_area, const char *text, int pos_x, int pos_y, int font_size, const Color &color);

private:
	// Size rate against window size 950 x 540
#if !defined(EMSCRIPTEN)
	static const Vector2 kScale;
#endif
	// Actual window size
	static const int kWindowWidth;	// Window width
	static const int kWindowHeight; // Window height
};

#endif // WINDOW_MANAGER_H