/*
 * app_proc.cc
 *
 *  Created on: June 20, 2024
 *      Author: Dong Won Kim
 */

#include "app_proc.h"

//--------------------------------------------------------------------------------------
// Initialization
//--------------------------------------------------------------------------------------
void AppProc::Initialize()
{
#if defined(EMSCRIPTEN)
    const char *button_sound_file_name = "/audio/button.wav";
    const char *hit_bar_sound_file_name = "/audio/hit.wav";
    const char *hit_block_sound_file_name = "/audio/shoot.wav";
#else
    const char *button_sound_file_name = "./resources/audio/button.wav";
    const char *hit_bar_sound_file_name = "./resources/audio/hit.wav";
    const char *hit_block_sound_file_name = "./resources/audio/shoot.wav";
#endif

    const Sound play_button_sound = LoadSound(button_sound_file_name);
    const Sound end_button_sound = LoadSoundAlias(play_button_sound);
    const Sound hit_bar_sound = LoadSound(hit_bar_sound_file_name);     // Load hitting bar audio file
    const Sound hit_block_sound = LoadSound(hit_block_sound_file_name); // Load hitting block audio file
    // SetMasterVolume(0.1f);
    // SetSoundVolume(hit_bar_sound, 0.1f);
    // Music background_sound = LoadMusicStream("./resources/audio/background.wav"); // Load background sound audio file
    // background_sound.looping = true;
    // SetMusicVolume(background_sound, kBackgroundSoundVolumn);
    // PlayMusicStream(background_sound);

    // Initialize HUD
    if (Screen::IsMobile())
    {
        hud_ = new HUD();
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
    play_button_ = new Button(play_button_texture, play_button_sound, -130.0f);
    const Texture2D end_button_texture = LoadTexture(end_button_texture_file_name);
    end_button_ = new Button(end_button_texture, end_button_sound, 1.0f);

    // Loading game objects
    //----------------------------------------------------------------------------------
    bool is_incomplete_tutorial = false;
    if (FileExists(StorageValue::storage_data_file()))
    {
        const int level_num = StorageValue::LoadStorageValue(kStoragePositionLevel);
        const int num_of_blocks = StorageValue::LoadStorageValue(kStoragePositionNumOfBlock);
        const unsigned int score = StorageValue::LoadStorageValue(kStoragePositionScore);
        const unsigned int high_score = StorageValue::LoadStorageValue(kStoragePositionHighScore);
        is_incomplete_tutorial = StorageValue::LoadStorageValue(kStoragePositionTutorial);

        level_ = new Level(level_num, num_of_blocks, RAYWHITE);
        player_ = new Player(*level_);
        player_->score(score);
        player_->high_score(high_score);
    }
    else
    {
        level_ = new Level(1, 7, RAYWHITE);
        player_ = new Player(*level_);
    }
    playing_bar_ = new PlayingBar(MAROON);
    ball_ = new Ball(hit_bar_sound, hit_block_sound, MAROON, playing_bar_->GraphicsEntity::position().y, level_->ball_speed());

    // Setting up tutorials for player
    if (level_->level_num() == 1 || is_incomplete_tutorial)
    {
        if (Screen::IsMobile())
        {
            // Define tutorial ending condtion
            TutorialCondition move_to_left_condition = *hud_->left_control();
            TutorialCondition move_to_right_condition = *hud_->right_control();
            TutorialCondition start_game_condition = *playing_bar_;
            TutorialCondition hit_ball_back_condition = *hud_->hit_back_control();

            player_->tutorials(std::make_unique<TutorialCondition>(move_to_left_condition), std::make_unique<TutorialCondition>(move_to_right_condition), std::make_unique<TutorialCondition>(start_game_condition), std::make_unique<TutorialCondition>(hit_ball_back_condition));
        }
        else
        {
            // Define tutorial ending condtion
            TutorialCondition hit_ball_back_condition = *ball_;

            player_->tutorials(std::make_unique<TutorialCondition>(hit_ball_back_condition));
        }
    }
}

//--------------------------------------------------------------------------------------
// De-Initialization
//--------------------------------------------------------------------------------------
void AppProc::Deinitialize()
{
    UnloadTexture(play_button_->texture()); // Unload button texture
    UnloadTexture(end_button_->texture());  // Unload button texture

    UnloadSound(play_button_->sound());     // Unload sound data
    UnloadSoundAlias(end_button_->sound()); // Unload sound data
    UnloadSound(ball_->hit_bar_sound());    // Unload sound data
    UnloadSound(ball_->hit_block_sound());  // Unload sound data

    // UnloadMusicStream(background_sound);          // Unload music stream buffers from RAM
}

//----------------------------------------------------------------------------------
// Updating objects' activities per frame
//----------------------------------------------------------------------------------
void AppProc::UpdateDrawFrame()
{
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    // UpdateMusicStream(background_sound);      // Update music buffer with new stream data

    if (player_->state() == kIntro)
    {
        UpdateIntroduction();
    }
    else if (player_->state() == kPlay)
    {
        UpdatePlay();
    }
    else if (player_->state() == kOut)
    {
        UpdateOut();
    }
    else if (player_->state() == kLevelUp)
    {
        UpdateLevelUp();
    }
    else if (player_->state() == kEnd)
    {
        UpdateEnd();
    }
    else if (player_->state() == kGoodbye)
    {
        UpdateGoodbye();
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    if (player_->state() == kIntro)
    {
        DrawIntroduction();
    }
    else if (player_->state() == kPlay)
    {
        DrawPlay();
    }
    else if (player_->state() == kOut)
    {
        DrawOut();
    }
    else if (player_->state() == kLevelUp)
    {
        DrawLevelUp();
    }
    else if (player_->state() == kGoodbye)
    {
        DrawGoodbye();
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// Update for introduction stage
void AppProc::UpdateIntroduction()
{
    play_button_->state(kNormal);
    play_button_->activated(false);

    end_button_->state(kNormal);
    end_button_->activated(false);

    // Get mouse position
    mouse_position_ = GetMousePosition();
    play_button_->CheckClick(mouse_position_);
    end_button_->CheckClick(mouse_position_);

    if (play_button_->activated())
    {
        player_->state(kPlay);
    }
    else if (end_button_->activated())
    {
        player_->state(kEnd);
        WaitTime(0.2); // Wait 0.2 seconds
    }
}

// Update for playing stage
void AppProc::UpdatePlay()
{
    if (IsKeyDown(KEY_ESCAPE))
        player_->state(kIntro);

    bool has_gesture = false; // For mobile device

    // Moving playing bar
    if (Screen::IsMobile())
    {
        hud_->last_gesture(hud_->current_gesture());
        hud_->current_gesture(GetGestureDetected());
        if (hud_->current_gesture() != hud_->last_gesture() && (hud_->current_gesture() == GESTURE_TAP || hud_->current_gesture() == GESTURE_HOLD || hud_->current_gesture() == GESTURE_DOUBLETAP || hud_->current_gesture() == GESTURE_DRAG))
        {
            has_gesture = true;
        }
    }

    // Dealing with tutorials
    auto tutorials = player_->tutorials();
    unsigned long index = player_->current_tutorial_idx();
    if (!tutorials.empty() && index < tutorials.size())
    {
        std::shared_ptr<Tutorial> &tutorial = tutorials.at(index); // For updating tutorial properties
        auto tutorial_condition = tutorial->tutorial_condition();

        if (!tutorial->started())
        {
            tutorial->started(true); // Start simple tutorial
            if (tutorial_condition)
            {
                tutorial_condition->condition_started(true); // Start complex tutorial with condition to complete
            }
        }
        else
        {
            if (!tutorial_condition)
            {
                bool triggered{false};
                if (Screen::IsMobile() && has_gesture)
                {
                    triggered = IsMouseButtonPressed(tutorial->input_method().mouse_button);
                }
                else
                {
                    triggered = IsKeyDown(tutorial->input_method().keyboard_key);
                }

                if (!tutorial->completed() && triggered)
                {
                    tutorial->completed(true); // Finish simple tutorial
                    player_->current_tutorial_idx(++index);
                }
            }
            else if (tutorial_condition->condition_achieved())
            {
                tutorial->completed(true); // Finish complex tutorial with condition
                player_->current_tutorial_idx(++index);
            }
        }
    }

    if (Screen::IsMobile() && has_gesture)
    {
        playing_bar_->Move(hud_);
    }
    else
    {
        playing_bar_->Move();
    }

    // Start playing game by pressing space bar or touching upper part of screen for a mobile device
    if (Screen::IsMobile())
    {
        if (ball_->held() && playing_bar_->IsPlayingBarTouched())
        {
            if (playing_bar_->condition_achieved())
            {
                ball_->held(false);
            }
            else if (playing_bar_->condition_started()) // Tutorial condition is met
            {
                playing_bar_->condition_achieved(true);
                ball_->held(false);
            }
        }
    }
    else
    {
        if (ball_->held() && IsKeyDown(KEY_SPACE))
        {
            ball_->held(false);
        }
    }

    const Rectangle play_bar_shape = playing_bar_->shape();

    // Bouncing ball logic
    if (!ball_->held())
    {
        ball_->Move();
    }
    else
    {
        ball_->position_x(playing_bar_->position_x() + play_bar_shape.width / 2); // Move along with the playing bar
    }

    // When the ball hits the playing bar
    if (ball_->IsCollided(play_bar_shape) && !ball_->held())
    {
        ball_->PlayHitBarSound();

        // Hit back in the same direction
        if (Screen::IsMobile() && has_gesture)
        {
            ball_->Collide(hud_, play_bar_shape, level_->level_num());
        }
        else
        {
            ball_->Collide(play_bar_shape, level_->level_num());
        }
    }

    // When the ball hits blocks
    Block *blocks = std::move(level_->blocks());
    if (const int block_num = ball_->block_collided_with(blocks, level_->number_of_blocks()) != -1)
    {
        if (ball_->risk_rate() > 2)
        {
            player_->state(kOut);
        }
        else
        {
            ball_->PlayHitBlockSound();
            ball_->Collide(blocks[block_num].shape(), ball_->speed());
            player_->AddScore(blocks[block_num].score());
        }
    }

    // Falling blocks after collision
    //----------------------------------------------------------------------------------
    level_->Fall();

    if (level_->IsLevelFinished())
    {
        if (level_->level_num() < Level::kMaxLevelNumber)
            player_->state(kLevelUp); // Player goes to the next level
        else
            player_->state(kEnd); // Player ends the game after finishing all levels
    }
}

// Update for out stage after losing game, trying the same level again
void AppProc::UpdateOut()
{
    ball_->held(true);

    const int level_num = level_->level_num();
    const int num_of_blocks = level_->number_of_blocks();

    // Delete current level
    delete level_;

    // Load new level data
    level_ = new Level(level_num, num_of_blocks, RAYWHITE);

    // Initialize game objects
    player_->level(*level_);

    // Load score from storage
    const unsigned int score = StorageValue::LoadStorageValue(kStoragePositionScore);
    player_->score(score);

    playing_bar_->default_position();

    ball_->default_position(playing_bar_->GraphicsEntity::position().y);
    ball_->speed(level_->ball_speed());
    ball_->held(true);
    ball_->enabled(true);
    ball_->risk_rate(0);

    WaitTime(2); // Wait 2 seconds

    player_->state(kPlay);
}

// Update for level up stage
void AppProc::UpdateLevelUp()
{
    ball_->held(true);

    // Save player's data
    int level_num = level_->level_num();
    StorageValue::SaveStorageValue(kStoragePositionLevel, level_num);

    const unsigned int score = player_->score();
    StorageValue::SaveStorageValue(kStoragePositionScore, score);

    const unsigned int high_score = player_->high_score();
    if (score > high_score)
    {
        player_->high_score(score);
        StorageValue::SaveStorageValue(kStoragePositionHighScore, score);
    }

    StorageValue::SaveStorageValue(kStoragePositionTutorial, player_->IsCompletedAllTutorials() ? 0 : 1); // If tutorial to complete exists, then 1. Otherwise, it is 0

    const int num_of_blocks = level_->number_of_blocks();

    // Delete current level
    delete level_;

    // Load new level data
    level_ = new Level(++level_num, num_of_blocks + 5, RAYWHITE);

    // Initialize game objects
    player_->level(*level_);
    playing_bar_->default_position();
    playing_bar_->speed(level_->level_num()); // Increase playing bar speed

    ball_->default_position(playing_bar_->GraphicsEntity::position().y);
    ball_->speed(level_->ball_speed());
    ball_->held(true);
    ball_->enabled(true);
    ball_->risk_rate(0);

    WaitTime(2); // Wait 2 seconds

    player_->state(kPlay);
}

// Update for end stage
void AppProc::UpdateEnd()
{
    // Save player's data
    StorageValue::SaveStorageValue(kStoragePositionLevel, level_->level_num());
    StorageValue::SaveStorageValue(kStoragePositionNumOfBlock, level_->number_of_blocks());
    StorageValue::SaveStorageValue(kStoragePositionHighScore, player_->high_score());
    StorageValue::SaveStorageValue(kStoragePositionTutorial, player_->IsCompletedAllTutorials() ? 0 : 1); // If tutorials to finish exist, then 1. Otherwise, it is 0

    player_->state(kGoodbye);
}

// Update for closing window
void AppProc::UpdateGoodbye()
{
    exit_window = WindowShouldClose(); // Detect window close button or ESC key
}

// Draw for introduction stage
void AppProc::DrawIntroduction()
{
    ClearBackground(kBackgroundColor);

    Screen::DisplayText(kCentre, "Easy Breakout", -150, -100, 40, GREEN);
    play_button_->Draw();
    end_button_->Draw();
}

// Draw for playing stage
void AppProc::DrawPlay()
{ // Playing game
    ClearBackground(level_->background_color());

    // Draw HUD
    if (Screen::IsMobile())
    {
        hud_->Draw();
    }

    level_->Draw();
    playing_bar_->Draw();
    ball_->Draw();

    // Presenting player current level
    const std::string player_level = "Level : " + std::to_string(level_->level_num());
    Screen::DisplayText(kLeft, player_level.c_str(), 10, 10, 20, DARKGRAY);

    // Presenting offensive rate
    const std::string offensive_rate = "Risk rate : " + std::to_string(ball_->risk_rate());
    Screen::DisplayText(kMiddle, offensive_rate.c_str(), -50, 10, 20, DARKGRAY);

    // const std::string ball_speed = "Ball speed : (" + std::to_string(ball->speed().x) + ", " + std::to_string(ball->speed().y) + ")";
    // Screen::DisplayText(kMiddle, ball_speed.c_str(), -50, 10, 20, DARKGRAY);

    // const std::string window_size = "Window size : (" + std::to_string(Screen::window_size().width) + ", " + std::to_string(Screen::window_size().height) + ")";
    // Screen::DisplayText(kMiddle, window_size.c_str(), -50, 10, 20, DARKGRAY);

    // const std::string window_scale = "Window scale : (" + std::to_string(Screen::scale().x) + ", " + std::to_string(Screen::scale().y) + ")";
    // Screen::DisplayText(kMiddle, window_scale.c_str(), -50, 10, 20, DARKGRAY);

    // Presenting player's score
    const std::string player_score = "Score : " + std::to_string(player_->score());
    Screen::DisplayText(kRight, player_score.c_str(), -140, 10, 20, DARKGRAY);

    // Presenting tutorial instructions
    auto tutorials = player_->tutorials();
    unsigned long index = player_->current_tutorial_idx();
    if (!tutorials.empty() && index < tutorials.size())
    {
        std::shared_ptr<Tutorial> &tutorial = tutorials.at(index);
        if (tutorial->started() && !tutorial->completed())
        {
            Screen::DisplayText(kBottomLeft, tutorial->instruction(), 50, -100, 20, RED);
        }
    }

    if (Screen::IsMobile())
    {
        if (ball_->held())
        {
            Screen::DisplayText(kBottomRight, "Touch bar under ball to start.", -350, -50, 20, Fade(GRAY, 0.5f));
        }
    }
    else
    {
        if (ball_->held())
        {
            Screen::DisplayText(kBottomRight, "Press space bar to start.", -275, -50, 20, Fade(GRAY, 0.5f));
        }
    }
}

// Draw for out stage
void AppProc::DrawOut()
{
    ClearBackground(kBackgroundColor);

    Screen::DisplayText(kCentre, "Try again!", -100, -100, 40, RED);
}

// Draw for level up stage
void AppProc::DrawLevelUp()
{
    ClearBackground(kBackgroundColor);

    Screen::DisplayText(kCentre, "Level up!", -100, -100, 40, BLACK);
}

// Draw for goodbye screen
void AppProc::DrawGoodbye()
{
    ClearBackground(kBackgroundColor);

    Screen::DisplayText(kCentre, "Goodbye!", -100, -100, 40, GRAY);

    // Presenting player's high score
    const std::string player_high_score = "High score : " + std::to_string(player_->high_score());
    Screen::DisplayText(kCentre, player_high_score.c_str(), -160, -10, 40, GRAY);
}
