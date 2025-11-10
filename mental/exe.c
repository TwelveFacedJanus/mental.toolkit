// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/mental.h"


int main(int argc, const char* argv[])
{
    arguments_checker(argc, argv);
    
    
    MentalApplicationInfo appInfo = {
        .eType = MENTAL_STRUCTURE_TYPE_APPLICATION_INFO,
        .aVersion = {1, 0, 0},
        .pApplicationName = "Telegram bot",
        .pAuthor = "Daniil (TwelveFacedJanus) Ermolaev"
    };

    MentalApplication app = {
        .eType = MENTAL_STRUCTURE_TYPE_APPLICATION,
        .pInfo = &appInfo,
    };

    mentalCreateApplication(&app);

    MentalStorageInfo storageInfo = {
        .eType = MENTAL_STRUCTURE_TYPE_STORAGE_INFO,
        .eStype = MENTAL_STORAGE_TYPE_IN_MEMORY,
    };

    MentalStorage storage = {
        .eType = MENTAL_STRUCTURE_TYPE_STORAGE,
        .pInfo = &storageInfo,
    };

    mentalCreateStorage(&storage);
    
    /* Пример использования mentalUpdateInMemoryStorage для разных типов данных */
    
    /* 1. Сохранение строки */
    KVValue stringValue;
    stringValue.type = KV_TYPE_STRING;
    strncpy(stringValue.value.string_value, "Hello, Storage!", MAX_VALUE_SIZE - 1);
    stringValue.value.string_value[MAX_VALUE_SIZE - 1] = '\0';
    mentalUpdateInMemoryStorage(&storage, "message", stringValue);
    
    /* 2. Сохранение числа (int) */
    KVValue intValue = {
        .type = KV_TYPE_INT,
        .value.int_value = 42
    };
    mentalUpdateInMemoryStorage(&storage, "count", intValue);
    
    /* 3. Сохранение числа с плавающей точкой */
    KVValue doubleValue = {
        .type = KV_TYPE_DOUBLE,
        .value.double_value = 3.14159
    };
    mentalUpdateInMemoryStorage(&storage, "pi", doubleValue);
    
    /* 4. Сохранение булевого значения */
    KVValue boolValue = {
        .type = KV_TYPE_BOOL,
        .value.bool_value = true
    };
    mentalUpdateInMemoryStorage(&storage, "enabled", boolValue);
    mentalPrintInMemoryStorage(&storage);
    mentalDestroyStorage(&storage);


    printf("Hello, World!\n");
    return 0;
}
