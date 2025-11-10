// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "storage.h"

MentalResult mentalCreateStorage(MentalStorage *pStorage) {
    if (pStorage == null || pStorage->pInfo == null) return MENTAL_RESULT_POINTER_IS_NULL;

    if (pStorage->pInfo->eStype == MENTAL_STORAGE_TYPE_IN_MEMORY) mentalCreateInMemoryStorage(pStorage);

    return MENTAL_RESULT_OK;
}


MentalResult mentalCreateInMemoryStorage(MentalStorage* pStorage)
{
    if (pStorage == null) return MENTAL_RESULT_POINTER_IS_NULL;

    pStorage->pNext = (void*)kv_create(50);
    if (pStorage->pNext == null) return MENTAL_RESULT_FAILED_TO_ALLOCATE_MEMORY;

    return MENTAL_RESULT_OK;
}

MentalResult mentalDestroyStorage(MentalStorage *pStorage)
{
    if (pStorage == null) return MENTAL_RESULT_POINTER_IS_NULL;
    if (pStorage->pNext != null) kv_destroy((KVStore*)pStorage->pNext);
    return MENTAL_RESULT_OK;
}

MentalResult mentalUpdateInMemoryStorage(MentalStorage *pStorage, const char* key, KVValue value)
{
    if (pStorage == null) return MENTAL_RESULT_POINTER_IS_NULL;
    if (pStorage->pInfo == null) return MENTAL_RESULT_POINTER_IS_NULL;
    if (pStorage->pInfo->eStype != MENTAL_STORAGE_TYPE_IN_MEMORY) return MENTAL_RESULT_ERROR;
    if (pStorage->pNext == null) return MENTAL_RESULT_POINTER_IS_NULL;
    if (key == null) return MENTAL_RESULT_POINTER_IS_NULL;

    KVStore* store = (KVStore*)pStorage->pNext;
    bool success = false;

    /* Вызываем соответствующую функцию kv_put в зависимости от типа значения */
    switch (value.type) {
        case KV_TYPE_STRING:
            success = kv_put_string(store, key, value.value.string_value);
            break;
        case KV_TYPE_INT:
            success = kv_put_int(store, key, value.value.int_value);
            break;
        case KV_TYPE_DOUBLE:
            success = kv_put_double(store, key, value.value.double_value);
            break;
        case KV_TYPE_BOOL:
            success = kv_put_bool(store, key, value.value.bool_value);
            break;
        case KV_TYPE_BINARY:
            success = kv_put_binary(store, key, value.value.binary.data, value.value.binary.size);
            break;
        default:
            return MENTAL_RESULT_ERROR;
    }

    return success ? MENTAL_RESULT_OK : MENTAL_RESULT_ERROR;
}


MentalResult mentalPrintInMemoryStorage(MentalStorage *pStorage)
{
    if (pStorage == null) return MENTAL_RESULT_POINTER_IS_NULL;

    kv_print_all((KVStore*)pStorage->pNext);

    return MENTAL_RESULT_OK;
}
