#ifndef MENTAL_H
#define MENTAL_H

#include <stdlib.h>

typedef enum MentalStructureType
{
    MENTAL_STRUCTURE_TYPE_APPLICATION_INFO = 0,
    MENTAL_STRUCTURE_TYPE_APPLICATION = 1,

    MENTAL_STRUCTURE_TYPE_STORAGE_INFO = 2,
    MENTAL_STRUCTURE_TYPE_STORAGE = 3,
} MentalStructureType;

typedef enum MentalResult
{
    MENTAL_RESULT_OK = 0,
    MENTAL_RESULT_ERROR = -1,
    MENTAL_RESULT_UNDEFINED_ERROR = -2,
    MENTAL_RESULT_FAILED_TO_ALLOCATE_MEMORY = -3,
    MENTAL_RESULT_POINTER_IS_NULL = -4,
    MENTAL_RESULT_POINTER_IS_NOT_NULL = -5,
} MentalResult;

#define null NULL

typedef struct MentalApplicationInfo
{
    MentalStructureType eType;
    uint8_t     aVersion[3];
    const char* pApplicationName;
    const char* pAuthor;
    const void* pNext;
} MentalApplicationInfo;

typedef struct MentalApplication
{
    MentalStructureType eType;
    MentalApplicationInfo *pInfo;
    const void* pNext;
} MentalApplication;

#include "../utils/common.h"

MentalResult mentalCreateApplication(MentalApplication *pApplication);

#include "../storage/storage.h"

#endif // MENTAL_H
