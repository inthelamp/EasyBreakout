/*
 * EasyBreakout.h
 *
 *  Created on: Aug. 31, 2023
 *      Author: Dong Won Kim
 */

#ifndef EASY_BREAKOUT_
#define EASY_BREAKOUT_

// Screen size
#define SCREEN_WIDTH                960             // Screen width       
#define SCREEN_HEIGHT               540             // Screen height 

// Audio definition
#define BACKGROUND_SOUND_VOLUMN     0.2f            // Background sound volumn, 1.0 is maximum

// Ball definition
#define BALL_RADIUS                 10              // Ball radius
#define INIT_BALL_SPEED_X           4.0f            // Initial ball speed on x-axis 
#define INIT_BALL_SPEED_Y           -5.0f           // Initial ball speed on y-axis 
#define BALL_SPEED_INCREMENT_RATE   1/5             // Ball speed increment due to game level
#define BALL_RANDOM_SPEED_RATE_ON_X (GetRandomValue(5, 20) / 10)

// Block definition
#define BLOCK_FALLING_SPEED         5.0f            // Block falling speed on y-axis

// Getting complementary color 
#define COMPLEMENTARY_COLOR(r, g, b) {static_cast<unsigned char>(255 - (int)r), static_cast<unsigned char>(255 - (int)g), static_cast<unsigned char>(255 - (int)b), 0xff}

// Playing bar definition
#define PLAYING_BAR_POS_Y           (float)SCREEN_HEIGHT - 50   // Playing bar position on y-axis

// Storage definition
#define STORAGE_DATA_FILE           "storage.data"  // Storage file 
// NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum {
    STORAGE_POSITION_SCORE      = 0,
    STORAGE_POSITION_HISCORE    = 1
} StorageData;

// Persistent storage functions
static bool SaveStorageValue(unsigned int position, int value);
static int LoadStorageValue(unsigned int position);

#endif // EASY_BREAKOUT_ 