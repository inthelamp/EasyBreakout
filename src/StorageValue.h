/*
 * StorageValue.h
 *
 *  Created on: Sep. 08, 2023
 *      Author: Dong Won Kim
 */

#ifndef STORAGE_VALUE_H_
#define STORAGE_VALUE_H_

// Storage definition
const char * STORAGE_DATA_FILE = "storage.data";

// NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum {
    STORAGE_POSITION_SCORE      = 0,
    STORAGE_POSITION_HISCORE    = 1
} StorageData;

// Persistent storage functions
static bool SaveStorageValue(unsigned int position, int value);
static int LoadStorageValue(unsigned int position);


#endif // STORAGE_VALUE_H_