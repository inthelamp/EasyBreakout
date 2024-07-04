/*
 * screen.h
 *
 *  Created on: Sept. 26, 2023
 *      Author: Dong Won Kim
 */

#ifndef SCREEN_H_
#define SCREEN_H_

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
class Screen
{
public:
	Screen() = delete;

	constexpr static int kMinWidth = 480;  // Minimum window width
	constexpr static int kMinHeight = 270; // Minimum window height
	constexpr static int kMaxWidth = 960;  // Minimum window width
	constexpr static int kMaxHeight = 540; // Minimum window height

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
		width = width < kMinWidth ? kMinWidth : width;
		width = width > kMaxWidth ? kMaxWidth : width;
		height = height < kMinHeight ? kMinHeight : height;
		height = height > kMaxHeight ? kMaxHeight : height;
		return (Size){width, height};
	}
	constexpr static Vector2 scale() { return {kWidth / 960.0f, kHeight / 540.0f}; }
#else
	static const Vector2 scale() { return kScale; }
#endif
	constexpr static Size window_size() { return (Size){kWidth, kHeight}; }
	constexpr static bool IsMobile() { return kWidth <= 800 ? true : false; }
	// static const bool IsMobile() { return true; }
	static void DisplayText(const DisplayArea &display_area, const char *text, int pos_x, int pos_y, int font_size, const Color &color);

private:
	// Size rate against window size 960 x 540
#if !defined(EMSCRIPTEN)
	static const Vector2 kScale;
#endif
	// Actual window size
	static const int kWidth;  // Window width
	static const int kHeight; // Window height
};

#endif // SCREEN_H_