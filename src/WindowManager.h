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

// Vector2, 2 components
typedef struct Size
{
	int width;	// Vector x component
	int height; // Vector y component
} Size;

// Static class
class WindowManager
{
public:
	WindowManager() = delete;

	constexpr static int kWindowMinWidth = 480;	 // Minimum window width
	constexpr static int kWindowMinHeight = 270; // Minimum window height
	constexpr static int kWindowMaxWidth = 960;	 // Minimum window width
	constexpr static int kWindowMaxHeight = 540; // Minimum window height

// For Webassembly
#if defined(EMSCRIPTEN)
	static const Size web_window_size()
	{
		int width, height;
		emscripten_get_screen_size(&width, &height);

		if (width < height)
		{
			const int temp = width;
			width = height;
			height = temp;
		}

		height = width / 1.78;
		width *= 0.8;
		height *= 0.8;
		width = width < kWindowMinWidth ? kWindowMinWidth : width;
		width = width > kWindowMaxWidth ? kWindowMaxWidth : width;
		height = height < kWindowMinHeight ? kWindowMinHeight : height;
		height = height > kWindowMaxHeight ? kWindowMaxHeight : height;
		return (Size){width, height};
	}
	static const Vector2 scale() { return (Vector2){kWindowWidth / 960.0f, kWindowHeight / 540.0f}; }
#else
	static const Vector2 scale() { return kScale; }
#endif
	static const Size window_size() { return (Size){kWindowWidth, kWindowHeight}; }
	static const bool IsMobile() { return kWindowWidth < 640 ? true : false; }
	static void DisplayText(const DisplayArea &display_area, const char *text, int pos_x, int pos_y, int font_size, const Color &color);

private:
	// Size rate against window size 960 x 540
#if !defined(EMSCRIPTEN)
	static const Vector2 kScale;
#endif
	// Actual window size
	static const int kWindowWidth;	// Window width
	static const int kWindowHeight; // Window height
};

#endif // WINDOW_MANAGER_H