/*
 * StorageValue.h
 *
 *  Created on: Sep. 08, 2023
 *      Author: Dong Won Kim
 */

#ifndef STORAGE_VALUE_H_
#define STORAGE_VALUE_H_

#include <iostream>

#include "raylib.h"

// NOTE: Storage positions must start with 0, directly related to file memory layout
enum StorageData
{
    kStoragePositionLevel = 0,
    kStoragePositionNumOfBlock = 1,
    kStoragePositionScore = 2,
    kStoragePositionHighScore = 3
};

// Static class
class StorageValue
{
public:
    StorageValue() = delete;

    static const char *storage_data_file();

    // Persistent storage functions
    static const bool SaveStorageValue(unsigned int position, int value);
    static const int LoadStorageValue(unsigned int position);

private:
    static const char *kStorageDataFile;
};
#endif // STORAGE_VALUE_H_