#ifndef MENTAL_STORAGE_H
#define MENTAL_STORAGE_H

#include "../core/mental.h"
#include "kv/kv.h"

typedef enum MentalStorageType {
    MENTAL_STORAGE_TYPE_IN_MEMORY = 0,
    MENTAL_STORAGE_TYPE_LIKE_LOGS = 1,
    MENTAL_STORAGE_TYPE_ALICE = 2,
} MentalStorageType;

typedef struct MentalStorageInfo {
    MentalStructureType eType;
    MentalStorageType eStype;
    char* pName;
    void* pNext;
} MentalStorageInfo;

typedef struct MentalStorage {
    MentalStructureType eType;
    MentalStorageInfo *pInfo;
    void* pNext;
} MentalStorage;

MentalResult mentalCreateStorage(MentalStorage *pStorage);
MentalResult mentalCreateInMemoryStorage(MentalStorage *pStorage);
MentalResult mentalUpdateInMemoryStorage(MentalStorage *pStorage, const char* key, KVValue value);
MentalResult mentalPrintInMemoryStorage(MentalStorage *pStorage);
MentalResult mentalDestroyStorage(MentalStorage *pStorage);


#endif // MENTAL_STORAGE_H
