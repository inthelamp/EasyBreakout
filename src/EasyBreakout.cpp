/*
 * EasyBreakout.cpp
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#include "EasyBreakout.h"

// Define global variables
HUD *hud = nullptr;
Level *level = nullptr;
Player *player = nullptr;
PlayingBar *playingBar = nullptr;
Ball *ball = nullptr;
Button *play_button = nullptr;
Button *end_button = nullptr;
Vector2 mouse_point = {0.0f, 0.0f};
bool exit_window = false;

//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void); // Update and Draw one frame

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //----------------------------------------------------------------------------------
    // Initialization
    //----------------------------------------------------------------------------------

    // Loading game data
    //----------------------------------------------------------------------------------

    // Initializing window
    //----------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT); // Make the window resizable
    InitWindow(WindowManager::window_size().width, WindowManager::window_size().height, "EasyBreakout");
    SetWindowMinSize(WindowManager::kWindowMinWidth, WindowManager::kWindowMinHeight);

    // Initializing game sound
    //--------------------------------------------------------------------------------------
    InitAudioDevice(); // Initialize audio device

#if defined(EMSCRIPTEN)
    const char *button_sound_file_name = "/audio/button.wav";
    const char *hit_bar_sound_file_name = "/audio/hit.wav";
    const char *hit_block_sound_file_name = "/audio/shoot.wav";
#else
    const char *button_sound_file_name = "./resources/audio/button.wav";
    const char *hit_bar_sound_file_name = "./resources/audio/hit.wav";
    const char *hit_block_sound_file_name = "./resources/audio/shoot.wav";
#endif

    const Sound button_sound = LoadSound(button_sound_file_name);
    const Sound hit_bar_sound = LoadSound(hit_bar_sound_file_name);     // Load hitting bar audio file
    const Sound hit_block_sound = LoadSound(hit_block_sound_file_name); // Load hitting block audio file
    SetMasterVolume(0.1f);
    // SetSoundVolume(hit_bar_sound, 0.1f);
    // Music background_sound = LoadMusicStream("./resources/audio/background.wav");  // Load background sound audio file
    // background_sound.looping = true;
    // SetMusicVolume(background_sound, BACKGROUND_SOUND_VOLUMN);
    // PlayMusicStream(background_sound);

    // Initialize HUD
    if (WindowManager::IsMobile())
    {
        hud = new HUD();
    }

    // Loading buttons

#if defined(EMSCRIPTEN)
    const char *play_button_texture_file_name = "/images/play_buttons.png";
    const char *end_button_texture_file_name = "/images/end_buttons.png";
#else
    const char *play_button_texture_file_name = "./resources/images/play_buttons.png";
    const char *end_button_texture_file_name = "./resources/images/end_buttons.png";
#endif

    const Texture2D play_button_texture = LoadTexture(play_button_texture_file_name);
    play_button = new Button(play_button_texture, &button_sound, -130);

    const Texture2D end_button_texture = LoadTexture(end_button_texture_file_name);
    end_button = new Button(end_button_texture, &button_sound, 10);

    // Loading game objects
    //----------------------------------------------------------------------------------
    int has_incomplete_tutorial = 0;
    if (FileExists(StorageValue::storage_data_file()))
    {
        const int level_num = StorageValue::LoadStorageValue(kStoragePositionLevel);
        const int num_of_blocks = StorageValue::LoadStorageValue(kStoragePositionNumOfBlock);
        const unsigned int score = StorageValue::LoadStorageValue(kStoragePositionScore);
        const unsigned int high_score = StorageValue::LoadStorageValue(kStoragePositionHighScore);
        has_incomplete_tutorial = StorageValue::LoadStorageValue(kStoragePositionTutorial);

        level = new Level(level_num, num_of_blocks, RAYWHITE);
        player = new Player(*level);
        player->set_score(score);
        player->set_high_score(high_score);
    }
    else
    {
        level = new Level(1, 7, RAYWHITE);
        player = new Player(*level);
    }
    playingBar = new PlayingBar(MAROON);
    ball = new Ball(hit_bar_sound, hit_block_sound, MAROON, playingBar->get_position().y, level->get_ball_speed());

    // Setting up tutorials for player
    if (level->get_level_num() == 1 || has_incomplete_tutorial)
    {
        if (WindowManager::IsMobile())
        {
            player->set_tutorials(std::shared_ptr<TutorialCondition>(hud->left_control()), std::shared_ptr<TutorialCondition>(hud->right_control()), std::shared_ptr<TutorialCondition>(playingBar), std::shared_ptr<TutorialCondition>(hud->hit_back_control()));
        }
        else
        {
            player->set_tutorials(std::shared_ptr<TutorialCondition>(ball));
        }
    }

#if defined(EMSCRIPTEN)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exit_window)
    {
        UpdateDrawFrame();
    }
#endif

    //--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(play_button_texture); // Unload button texture
    UnloadTexture(end_button_texture);  // Unload button texture

    UnloadSound(hit_block_sound); // Unload sound data
    UnloadSound(hit_bar_sound);   // Unload sound data
    UnloadSound(button_sound);

    // UnloadMusicStream(background_sound);          // Unload music stream buffers from RAM

    // Deleting dynamic storages
    //-------------------------------------------------------------------------------------
    if (WindowManager::IsMobile())
    {
        delete hud;
    }

    delete ball;
    delete playingBar;
    delete level;

    // Deleting buttons
    delete play_button;
    delete end_button;

    CloseAudioDevice(); // Close audio device

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame()
{
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    // UpdateMusicStream(background_sound);      // Update music buffer with new stream data

    if (player->state() == kIntro)
    {
        play_button->set_state(kNormal);
        play_button->set_activated(false);

        end_button->set_state(kNormal);
        end_button->set_activated(false);

        mouse_point = GetMousePosition();
        play_button->check_click(mouse_point);
        end_button->check_click(mouse_point);

        if (play_button->is_activated())
        {
            player->set_state(kPlay);
        }
        else if (end_button->is_activated())
        {
            player->set_state(kEnd);
            WaitTime(0.2); // Wait 0.2 seconds
        }
    }
    else if (player->state() == kPlay)
    {
        if (IsKeyDown(KEY_ESCAPE))
            player->set_state(kIntro);

        bool has_gesture = false; // For mobile device

        // Moving playing bat
        if (WindowManager::IsMobile())
        {
            hud->set_last_gesture(hud->current_gesture());
            hud->set_current_gesture(GetGestureDetected());
            if (hud->current_gesture() != hud->last_gesture() && (hud->current_gesture() == GESTURE_TAP || hud->current_gesture() == GESTURE_HOLD || hud->current_gesture() == GESTURE_DOUBLETAP || hud->current_gesture() == GESTURE_DRAG))
            {
                has_gesture = true;
            }
        }

        // Dealing with tutorials
        auto tutorials = player->tutorials().get();
        int index = player->current_tutorial_idx();
        if (!tutorials->empty() && index < tutorials->size())
        {
            Tutorial &tutorial = tutorials->at(index); // For updating tutorial properties
            auto tutorial_condition = tutorial.tutorial_condition();

            if (!tutorial.started())
            {
                tutorial.set_started(true); // Start simple tutorial
                if (tutorial_condition)
                {
                    tutorial_condition->set_condition_started(true); // Start complex tutorial with condition to complete
                }
            }
            else
            {
                if (!tutorial_condition)
                {
                    bool triggered{false};
                    if (WindowManager::IsMobile() && has_gesture)
                    {
                        triggered = IsMouseButtonPressed(tutorial.input_method().mouse_button);
                    }
                    else
                    {
                        triggered = IsKeyDown(tutorial.input_method().keyboard_key);
                    }

                    if (!tutorial.completed() && triggered)
                    {
                        tutorial.set_completed(true); // Finish simple tutorial
                        player->set_current_tutorial_idx(++index);
                    }
                }
                else if (tutorial_condition->condition_achieved())
                {
                    tutorial.set_completed(true); // Finish complex tutorial with condition
                    player->set_current_tutorial_idx(++index);
                }
            }
        }

        if (WindowManager::IsMobile() && has_gesture)
        {
            playingBar->Move(hud);
        }
        else
        {
            playingBar->Move();
        }

        // Start playing game by pressing space bar or touching upper part of screen for a mobile device
        if (WindowManager::IsMobile())
        {
            if (ball->is_held() && playingBar->IsPlayingBarTouched())
            {
                if (playingBar->condition_achieved())
                {
                    ball->set_held(false);
                }
                else if (playingBar->condition_started()) // Tutorial condition is met
                {
                    playingBar->set_condition_achieved(true);
                    ball->set_held(false);
                }
            }
        }
        else
        {
            if (ball->is_held() && IsKeyDown(KEY_SPACE))
            {
                ball->set_held(false);
            }
        }

        const Rectangle play_bar_shape = playingBar->get_shape();

        // Bouncing ball logic
        if (!ball->is_held())
        {
            ball->Move();
        }
        else
        {
            ball->set_position_x(playingBar->get_position_x() + play_bar_shape.width / 2); // Move along with the playing bar
        }

        // When the ball hits the playing bar
        if (ball->IsCollided(play_bar_shape) && !ball->is_held())
        {
            ball->PlayHitBarSound();

            // Hit back in the same direction
            if (WindowManager::IsMobile() && has_gesture)
            {
                ball->Collide(hud, play_bar_shape, level->get_level_num());
            }
            else
            {
                ball->Collide(play_bar_shape, level->get_level_num());
            }
        }

        // When the ball hits blocks
        Block *blocks = std::move(level->get_blocks());
        if (const int block_num = ball->CollidedBlock(blocks, level->get_number_of_blocks()) != -1)
        {
            if (ball->get_risk_rate() > 2)
            {
                player->set_state(kOut);
            }
            else
            {
                ball->PlayHitBlockSound();
                ball->Collide(blocks[block_num].get_shape(), ball->get_speed());
                player->AddScore(blocks[block_num].get_point());
            }
        }

        // Falling blocks after collision
        //----------------------------------------------------------------------------------
        level->Fall();

        if (level->IsLevelFinished())
        {
            if (level->get_level_num() < Level::kMaxLevelNumber)
                player->set_state(kLevelUp); // Player goes to the next level
            else
                player->set_state(kEnd); // Player ends the game after finishing all levels
        }
    }
    else if (player->state() == kOut)
    { // Failed, try the same level again
        ball->set_held(true);

        const int level_num = level->get_level_num();
        const int num_of_blocks = level->get_number_of_blocks();

        // Delete current level
        delete level;

        // Load new level data
        level = new Level(level_num, num_of_blocks, RAYWHITE);

        // Initialize game objects
        player->set_level(*level);

        // Load score from storage
        const unsigned int score = StorageValue::LoadStorageValue(kStoragePositionScore);
        player->set_score(score);

        playingBar->set_default_position();

        ball->set_default_position(playingBar->get_position().y);
        ball->set_speed(level->get_ball_speed());
        ball->set_held(true);
        ball->set_enabled(true);
        ball->set_risk_rate(0);

        WaitTime(2); // Wait 2 seconds

        player->set_state(kPlay);
    }
    else if (player->state() == kLevelUp)
    {
        ball->set_held(true);

        // Save player's data
        int level_num = level->get_level_num();
        StorageValue::SaveStorageValue(kStoragePositionLevel, level_num);

        const unsigned int score = player->score();
        StorageValue::SaveStorageValue(kStoragePositionScore, score);

        const unsigned int high_score = player->high_score();
        if (score > high_score)
        {
            player->set_high_score(score);
            StorageValue::SaveStorageValue(kStoragePositionHighScore, score);
        }

        StorageValue::SaveStorageValue(kStoragePositionTutorial, player->TutorialsCompleted() ? 0 : 1); // If tutorial to complete exists, then 1. Otherwise, it is 0

        const int num_of_blocks = level->get_number_of_blocks();

        // Delete current level
        delete level;

        // Load new level data
        level = new Level(++level_num, num_of_blocks + 5, RAYWHITE);

        // Initialize game objects
        player->set_level(*level);
        playingBar->set_default_position();
        playingBar->set_speed(level->get_level_num()); // Increase playing bar speed

        ball->set_default_position(playingBar->get_position().y);
        ball->set_speed(level->get_ball_speed());
        ball->set_held(true);
        ball->set_enabled(true);
        ball->set_risk_rate(0);

        WaitTime(2); // Wait 2 seconds

        player->set_state(kPlay);
    }
    else if (player->state() == kEnd)
    {
        // Save player's data
        StorageValue::SaveStorageValue(kStoragePositionLevel, level->get_level_num());
        StorageValue::SaveStorageValue(kStoragePositionNumOfBlock, level->get_number_of_blocks());
        StorageValue::SaveStorageValue(kStoragePositionHighScore, player->high_score());
        StorageValue::SaveStorageValue(kStoragePositionTutorial, player->TutorialsCompleted() ? 0 : 1); // If tutorial to complete exists, then 1. Otherwise, it is 0

        player->set_state(kGoodbye);
    }
    else if (player->state() == kGoodbye)
    {
        exit_window = WindowShouldClose(); // Detect window close button or ESC key
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    // Introduction of game
    if (player->state() == kIntro)
    {
        ClearBackground(kBackgroundColor);

        WindowManager::DisplayText(kCentre, "Easy Breakout", -150, -100, 40, GREEN);
        play_button->Draw();
        end_button->Draw();
    }
    else if (player->state() == kPlay)
    { // Playing game
        ClearBackground(level->get_background_color());

        // Draw HUD
        if (WindowManager::IsMobile())
        {
            hud->Draw();
        }

        level->Draw();
        playingBar->Draw();
        ball->Draw();

        // Presenting player current level
        const std::string player_level = "Level : " + std::to_string(level->get_level_num());
        WindowManager::DisplayText(kLeft, player_level.c_str(), 10, 10, 20, DARKGRAY);

        // Presenting offensive rate
        const std::string offensive_rate = "Risk rate : " + std::to_string(ball->get_risk_rate());
        WindowManager::DisplayText(kMiddle, offensive_rate.c_str(), -50, 10, 20, DARKGRAY);

        // const std::string ball_speed = "Ball speed : (" + std::to_string(ball->get_speed().x) + ", " + std::to_string(ball->get_speed().y) + ")";
        // WindowManager::DisplayText(kMiddle, ball_speed.c_str(), -50, 10, 20, DARKGRAY);

        // const std::string window_size = "Window size : (" + std::to_string(WindowManager::window_width()) + ", " + std::to_string(WindowManager::window_height()) + ")";
        // WindowManager::DisplayText(kMiddle, window_size.c_str(), -50, 10, 20, DARKGRAY);

        // const std::string window_scale = "Window scale : (" + std::to_string(WindowManager::scale().x) + ", " + std::to_string(WindowManager::scale().y) + ")";
        // WindowManager::DisplayText(kMiddle, window_scale.c_str(), -50, 10, 20, DARKGRAY);

        // Presenting player's score
        const std::string player_score = "Score : " + std::to_string(player->score());
        WindowManager::DisplayText(kRight, player_score.c_str(), -140, 10, 20, DARKGRAY);

        // Presenting tutorial instructions
        auto tutorials = player->tutorials();
        int index = player->current_tutorial_idx();
        if (!tutorials->empty() && index < tutorials->size())
        {
            Tutorial &tutorial = tutorials->at(index);
            if (tutorial.started() && !tutorial.completed())
            {
                WindowManager::DisplayText(kBottomLeft, tutorial.instruction().c_str(), 50, -100, 20, RED);
            }
        }

        if (WindowManager::IsMobile())
        {
            if (ball->is_held())
            {
                WindowManager::DisplayText(kBottomRight, "Touch bar under ball to start.", -350, -50, 20, Fade(GRAY, 0.5f));
            }
        }
        else
        {
            if (ball->is_held())
            {
                WindowManager::DisplayText(kBottomRight, "Press space bar to start.", -275, -50, 20, Fade(GRAY, 0.5f));
            }
        }
    }
    else if (player->state() == kOut)
    {
        ClearBackground(kBackgroundColor);

        WindowManager::DisplayText(kCentre, "Try again!", -100, -100, 40, RED);
    }
    else if (player->state() == kLevelUp)
    {
        ClearBackground(kBackgroundColor);

        WindowManager::DisplayText(kCentre, "Level up!", -100, -100, 40, BLACK);
    }
    else if (player->state() == kGoodbye)
    {
        ClearBackground(kBackgroundColor);

        WindowManager::DisplayText(kCentre, "Goodbye!", -100, -100, 40, GRAY);

        // Presenting player's high score
        const std::string player_high_score = "High score : " + std::to_string(player->high_score());
        WindowManager::DisplayText(kCentre, player_high_score.c_str(), -160, -10, 40, GRAY);
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
}