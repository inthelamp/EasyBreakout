/*
 * EasyBreakout.cpp
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#include <iostream>
#include "raylib.h"

#include "Ball.h"
#include "MovingEntity.h"
#include "PlayingBar.h"
#include "Level.h"
#include "EasyBreakout.h"
#include "StorageValue.h"
#include "Block.h"
#include "Player.h"
#include "Button.h"

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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "EasyBreakout");

    // Loading game objects
    //----------------------------------------------------------------------------------
    Level * level = nullptr;
    Player * player = nullptr;

    if (FileExists(STORAGE_DATA_FILE)) {        
        const int level_num = LoadStorageValue(STORAGE_POSITION_LEVEL);     
        const int num_of_blocks = LoadStorageValue(STORAGE_POSITION_NUM_OF_BLOCKS);  
        const unsigned int score = LoadStorageValue(STORAGE_POSITION_SCORE);           
        const unsigned int high_score = LoadStorageValue(STORAGE_POSITION_HIGH_SCORE);                  

        level = new Level(RAYWHITE, level_num, num_of_blocks);
        player = new Player(level); 
        player->set_score(score);
        player->set_high_score(high_score);
    } else {
        level = new Level(RAYWHITE, 1, 7);
        player = new Player(level); 
    }
    PlayingBar * playingBar = new PlayingBar(MAROON);    
    Ball * ball = new Ball(MAROON, playingBar->get_position().y, level->get_ball_speed());

    // Initializing game sound
    //--------------------------------------------------------------------------------------
    InitAudioDevice();                                                          // Initialize audio device

    Sound button_sound = LoadSound("../assets/audio/button.wav");
    Sound hit_block_sound = LoadSound("../assets/audio/shoot.wav");             // Load hitting block audio file
    Sound hit_bar_sound = LoadSound("../assets/audio/hit.wav");                 // Load hitting bar audio file
    SetSoundVolume(hit_bar_sound, 0.5f);    
    // Music background_sound = LoadMusicStream("../assets/audio/background.wav"); // Load background sound audio file
    // background_sound.looping = true;
    // SetMusicVolume(background_sound, BACKGROUND_SOUND_VOLUMN);
    // PlayMusicStream(background_sound);

    // Loading buttons 
    Texture2D play_button_texture = LoadTexture("../assets/images/play_buttons.png");
    Button * play_button = new Button(&play_button_texture, &button_sound, SCREEN_WIDTH/2 - 130);

    Texture2D end_button_texture = LoadTexture("../assets/images/end_buttons.png");   
    Button * end_button = new Button(&end_button_texture, &button_sound, SCREEN_WIDTH/2 + 10);

    Vector2 mouse_point = { 0.0f, 0.0f };
    bool exitWindow = false;

    SetTargetFPS(60);                               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow)                             // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------        
        // Update
        //----------------------------------------------------------------------------------
        // UpdateMusicStream(background_sound);      // Update music buffer with new stream data 

        if (player->get_state() == intro) {      
            play_button->set_state(normal);
            play_button->set_activated(false);   

            end_button->set_state(normal); 
            end_button->set_activated(false);       

            mouse_point = GetMousePosition();      
            play_button->check_click(mouse_point);
            end_button->check_click(mouse_point);

            if (play_button->get_activated()) {
                player->set_state(play);                  
            } else if (end_button->get_activated()) {
                player->set_state(end);
                WaitTime(0.2);                                                        // Wait 0.2 seconds                       
            }   
        } else if (player->get_state() == play) {
            if (IsKeyDown(KEY_ESCAPE)) player->set_state(intro);

            // Moving playing bat
            playingBar->Move();

            // Bouncing ball logic
            if (ball->IsHeld() && IsKeyDown(KEY_SPACE)) ball->set_held(false);
            if (!ball->IsHeld()) {
                ball->Move();    
            } else {
                ball->set_position_x(playingBar->get_position_x() + playingBar->get_rec().width / 2); // Move along with the playing bar
            }   

            // When the ball hits the playing bar
            if (ball->IsCollided(playingBar->get_rec()) && !ball->IsHeld()) {
                PlaySound(hit_bar_sound);      
                ball->Collide(playingBar->get_rec(), level->get_level_num());
            }

            // When the ball hits blocks 
            Block * blocks = std::move(level->get_blocks());
            if ( const int block_num = ball->IsCollided(blocks, level->get_number_of_blocks()) != -1) {
                if (ball->get_risk_rate() > 2) {
                    player->set_state(out);
                } else {
                    PlaySound(hit_block_sound);
                    ball->Collide(blocks[block_num].get_rec(), ball->get_speed());
                    player->AddScore(blocks[block_num].get_point());    
                }                                            
            }

            // Falling blocks after collision
            //----------------------------------------------------------------------------------
            level->Fall();

            if (level->is_level_finished()) player->set_state(level_up);       // After completing the level, player goes to the next level   
        } else if (player->get_state() == out) {                               // Failed, try the same level again
            int level_num = level->get_level_num();
            int num_of_blocks = level->get_number_of_blocks();      

            // Delete current level
            delete level;

            // Load new level data
            Block::num_of_disabled_blocks = 0;
            level = new Level(RAYWHITE, level_num, num_of_blocks);

            // Initialize game objects
            player->set_level(level);

            // Load score from storage
            const unsigned int score = LoadStorageValue(STORAGE_POSITION_SCORE);
            player->set_score(score);

            playingBar->set_default_position();

            ball->set_default_position(playingBar->get_position().y);
            ball->set_speed(level->get_ball_speed());
            ball->set_held(true);
            ball->set_enabled(true);
            ball->set_risk_rate(0);
            
            WaitTime(2);                                                        // Wait 2 seconds

            player->set_state(play);          
        } else if (player->get_state() == level_up) {
            // Save player's data
            int level_num = level->get_level_num();            
            SaveStorageValue(STORAGE_POSITION_LEVEL, level_num);

            const unsigned int score = player->get_score();
            SaveStorageValue(STORAGE_POSITION_SCORE, score);

            const unsigned int high_score = player->get_high_score();
            if (score > high_score) {
                player->set_high_score(score);
                SaveStorageValue(STORAGE_POSITION_HIGH_SCORE, score);
            }    

            int num_of_blocks = level->get_number_of_blocks();      

            // Delete current level
            delete level;

            // Load new level data
            Block::num_of_disabled_blocks = 0;
            level = new Level(RAYWHITE, ++level_num, num_of_blocks + 5);

            // Initialize game objects
            player->set_level(level);
            playingBar->set_default_position();

            ball->set_default_position(playingBar->get_position().y);
            ball->set_speed(level->get_ball_speed());
            ball->set_held(true);
            ball->set_enabled(true);
            ball->set_risk_rate(0);            
            
            WaitTime(2);                                                        // Wait 2 seconds

            player->set_state(play);      
        } else if (player->get_state() == end) {
            // Save player's data         
            SaveStorageValue(STORAGE_POSITION_LEVEL, level->get_level_num());
            SaveStorageValue(STORAGE_POSITION_NUM_OF_BLOCKS, level->get_number_of_blocks());
            SaveStorageValue(STORAGE_POSITION_HIGH_SCORE, player->get_high_score());  

            player->set_state(goodbye);           
        }  else if (player->get_state() == goodbye) {
            exitWindow = WindowShouldClose();
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Introduction of game
            if (player->get_state() == intro) {
                ClearBackground(BACKGROUND_COLOR);

                DrawText("Easy Breakout", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 100 , 40, GREEN);
                play_button->Draw();       
                end_button->Draw();              
            } else  if (player->get_state() == play) {             // Playing game         
                ClearBackground(level->get_background_color());

                level->Draw();
                playingBar->Draw();            
                ball->Draw();

                // Presenting player current level
                const std::string player_level = "Level : " + std::to_string(level->get_level_num());                 
                DrawText(player_level.c_str(), 10, 10, 20, DARKGRAY);                  

                // Presenting offensive rate
                const std::string offensive_rate = "Risk rate : " + std::to_string(ball->get_risk_rate());            
                DrawText(offensive_rate.c_str(), SCREEN_WIDTH / 2 - 50, 10, 20, DARKGRAY);               
    
                // Presenting player score
                const std::string player_score = "Score : " + std::to_string(player->get_score());            
                DrawText(player_score.c_str(), SCREEN_WIDTH - 140, 10, 20, DARKGRAY);   
            } else if (player->get_state() == out) {
                ClearBackground(BACKGROUND_COLOR);   

                DrawText("Try again!", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 100 , 40, RED);
            } else if (player->get_state() == level_up) {
                ClearBackground(BACKGROUND_COLOR);       

                DrawText("Level up!", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 100 , 40, BLACK);
            } else if (player->get_state() == goodbye) {
                ClearBackground(BACKGROUND_COLOR); 

                DrawText("Goodbye!", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 100 , 40, GRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(play_button_texture);              // Unload button texture
    UnloadTexture(end_button_texture);               // Unload button texture   

    UnloadSound(hit_block_sound);                    // Unload sound data
    UnloadSound(hit_bar_sound);                      // Unload sound data  
    UnloadSound(button_sound);

    // UnloadMusicStream(background_sound);          // Unload music stream buffers from RAM

    // Deleting dynamic storages
    //-------------------------------------------------------------------------------------
    delete ball;
    delete playingBar;
    delete level;

    // Deleting buttons
    delete play_button;  
    delete end_button;

    CloseAudioDevice();                             // Close audio device

    CloseWindow();                                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Save integer value to storage file (to defined position)
// NOTE: Storage positions is directly related to file memory layout (4 bytes each integer)
bool SaveStorageValue(unsigned int position, int value)
{
    bool success = false;
    unsigned int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL)
    {
        if (dataSize <= (position*sizeof(int)))
        {
            // Increase data size up to position and store value
            newDataSize = (position + 1)*sizeof(int);
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if (newFileData != NULL)
            {
                // RL_REALLOC succeded
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value;
            }
            else
            {
                // RL_REALLOC failed
                TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", STORAGE_DATA_FILE, dataSize, position*sizeof(int));

                // We store the old size of the file
                newFileData = fileData;
                newDataSize = dataSize;
            }
        }
        else
        {
            // Store the old size of the file
            newFileData = fileData;
            newDataSize = dataSize;

            // Replace value on selected position
            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }

        success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
        RL_FREE(newFileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }
    else
    {
        TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);

        dataSize = (position + 1)*sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }

    return success;
}

// Load integer value from storage file (from defined position)
// NOTE: If requested position could not be found, value 0 is returned
int LoadStorageValue(unsigned int position)
{
    int value = 0;
    unsigned int dataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < (position*4)) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}