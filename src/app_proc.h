/*
 * app_proc.h
 *
 *  Created on: June 20, 2024
 *      Author: Dong Won Kim
 */

#ifndef APP_PROC_
#define APP_PROC_

// For WebAssembly
#if defined(EMSCRIPTEN)
#include <emscripten/emscripten.h>
#endif

#include <memory>

#include "raylib.h"

#include "screen.h"
#include "moving_entity.h"
#include "hud.h"
#include "button.h"
#include "level.h"
#include "block.h"
#include "playing_bar.h"
#include "ball.h"
#include "player.h"
#include "storage_value.h"

class AppProc
{
public:
    constexpr static int kFPS = 60;                       // Default frames per second
    constexpr static Color kBackgroundColor = RAYWHITE;   // Background color
    constexpr static float kBackgroundSoundVolumn = 0.2f; // Background sound volumn, 1.0 is maximum

    AppProc() = default;                          // constructor
    AppProc(const AppProc &) = delete;            // Copy constructor
    AppProc(AppProc &&) = delete;                 // Move constructor
    AppProc &operator=(const AppProc &) = delete; // Copy assignment operator
    AppProc &operator=(AppProc &&) = delete;      // Move assignment operator
    ~AppProc()                                    // destructor
    {
        if (Screen::IsMobile())
        {
            delete hud_;
        }

        delete ball_;
        delete level_;
        delete playing_bar_;
        delete player_;

        delete play_button_;
        delete end_button_;
    }

    void Initialize(void);      // Initialize app
    void UpdateDrawFrame(void); // Updating components' activities per frame
    void Deinitialize(void);    // Deinitialize app

    bool exit_window = false;

private:
    HUD *hud_{nullptr};
    Level *level_{nullptr};
    Player *player_{nullptr};
    PlayingBar *playing_bar_{nullptr};
    Ball *ball_{nullptr};
    Button *play_button_{nullptr};
    Button *end_button_{nullptr};

    Vector2 mouse_position_ = {0.0f, 0.0f}; // Coordinate where mouse points to

    void UpdateIntroduction();
    void UpdatePlay();
    void UpdateOut();
    void UpdateLevelUp();
    void UpdateEnd();
    void UpdateGoodbye();
    void DrawIntroduction();
    void DrawPlay();
    void DrawOut();
    void DrawLevelUp();
    void DrawGoodbye();
    void MakeTutorials(std::shared_ptr<TutorialCondition> &);
    void MakeTutorials(std::shared_ptr<TutorialCondition> &, std::shared_ptr<TutorialCondition> &, std::shared_ptr<TutorialCondition> &, std::shared_ptr<TutorialCondition> &);
};

#endif // APP_PROC_