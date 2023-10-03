/*
 * StorageValue.cpp
 *
 *  Created on: Sep. 27, 2023
 *      Author: Dong Won Kim
 */

#include "StorageValue.h"

// Storage definition
#if defined(EMSCRIPTEN)
const char *StorageValue::kStorageDataFile = "/data/storage.data";
#else
const char *StorageValue::kStorageDataFile = "./resources/data/storage.data";
#endif

const char *StorageValue::storage_data_file() { return kStorageDataFile; }

// Save integer value to storage file (to defined position)
// NOTE: Storage positions is directly related to file memory layout (4 bytes each integer)
bool const StorageValue::SaveStorageValue(unsigned int position, int value)
{
    bool success = false;
    unsigned int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(kStorageDataFile, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL)
    {
        if (dataSize <= (position * sizeof(int)))
        {
            // Increase data size up to position and store value
            newDataSize = (position + 1) * sizeof(int);
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
                TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", kStorageDataFile, dataSize, position * sizeof(int));

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

        success = SaveFileData(kStorageDataFile, newFileData, newDataSize);
        RL_FREE(newFileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", kStorageDataFile, value);
    }
    else
    {
        TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", kStorageDataFile);

        dataSize = (position + 1) * sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = SaveFileData(kStorageDataFile, fileData, dataSize);
        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", kStorageDataFile, value);
    }

    return success;
}

// Load integer value from storage file (from defined position)
// NOTE: If requested position could not be found, value 0 is returned
int const StorageValue::LoadStorageValue(unsigned int position)
{
    int value = 0;
    unsigned int dataSize = 0;
    unsigned char *fileData = LoadFileData(kStorageDataFile, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < (position * 4))
            TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", kStorageDataFile, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", kStorageDataFile, value);
    }

    return value;
}