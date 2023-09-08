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
#include "Player.h"

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
    //--------------------------------------------------------------------------------------
    Level * level = new Level(1, 15);
    Player * player = new Player(level); 
    PlayingBar * playingBar = new PlayingBar(MAROON);    
    Ball * ball = new Ball(MAROON, BALL_RADIUS, {(float)SCREEN_WIDTH/2, playingBar->get_position().y - BALL_RADIUS}, level->get_ball_speed());

    // Initializing game sound
    //--------------------------------------------------------------------------------------
    InitAudioDevice();      // Initialize audio device

    Sound hit_block_sound = LoadSound("../assets/audio/shoot.wav");             // Loading hitting block audio file
    Sound hit_bar_sound = LoadSound("../assets/audio/hit.wav");                 // Loading hitting bar audio file
    SetSoundVolume(hit_bar_sound, 0.5f);    
    Music background_sound = LoadMusicStream("../assets/audio/background.wav"); // Loding background sound audio file
    background_sound.looping = true;
    SetMusicVolume(background_sound, BACKGROUND_SOUND_VOLUMN);
    PlayMusicStream(background_sound);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------        
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(background_sound);      // Update music buffer with new stream data 

        // Moving playing bat
        playingBar->Move();

        // Bouncing ball logic
        if (ball->IsHeld() && IsKeyDown(KEY_SPACE)) ball->set_released();
        if (!ball->IsHeld()) {
            ball->Move();    
        } else {
            ball->set_position_x(playingBar->get_position_x() + playingBar->get_rec().width / 2); // Moving along with the playing bar
        }   

        // When the ball hits the playing bar
        if (ball->IsCollided(playingBar->get_rec()) && !ball->IsHeld()) {
            PlaySound(hit_bar_sound);      
            ball->Collide(playingBar->get_rec(), level->get_level_num());
        }

        // When the ball hits blocks 
        Block * blocks = std::move(level->get_blocks());
        if ( const int block_num = ball->IsCollided(blocks, level->get_number_of_blocks()) != -1) {
            PlaySound(hit_block_sound);
            ball->Collide(blocks[block_num].get_rec(), ball->get_speed());
            player->AddScore(blocks[block_num].get_point());
        }

        // Falling blocks after collision
        //----------------------------------------------------------------------------------
        level->Fall();

        // Update user information
        const std::string player_score = "Score : " + std::to_string(player->get_score());

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            level->Draw();
            playingBar->Draw();            
            ball->Draw();

            // Presenting player score
            DrawText(player_score.c_str(), 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //----------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(hit_block_sound);     // Unload sound data
    UnloadSound(hit_bar_sound);     // Unload sound data    
    UnloadMusicStream(background_sound);          // Unload music stream buffers from RAM

    // Deleting dynamic storages
    //-------------------------------------------------------------------------------------
    delete ball;
    delete playingBar;
    delete level;

    CloseAudioDevice();     // Close audio device

    CloseWindow();        // Close window and OpenGL context
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