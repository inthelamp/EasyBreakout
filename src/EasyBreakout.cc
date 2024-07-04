/*
 * EasyBreakout.cc
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#include "app_proc.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initializing window
    //----------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT); // Make the window resizable
    InitWindow(Screen::window_size().width, Screen::window_size().height, "Easy Breakout");
    SetWindowMinSize(Screen::kMinWidth, Screen::kMinHeight);

    // Initializing game sound
    //--------------------------------------------------------------------------------------
    InitAudioDevice(); // Initialize audio device

    //----------------------------------------------------------------------------------
    // Initialization app
    //----------------------------------------------------------------------------------
    AppProc app;
    app.Initialize();

#if defined(EMSCRIPTEN)
    emscripten_set_main_loop(app.UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(AppProc::kFPS); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!app.exit_window)
    {
        app.UpdateDrawFrame();
    }
#endif

    //----------------------------------------------------------------------------------
    // Deinitialization app
    //----------------------------------------------------------------------------------
    app.Deinitialize();

    // Close audio device
    CloseAudioDevice();

    // Close window and OpenGL context
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}