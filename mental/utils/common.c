// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "common.h"
#include <stddef.h>


void arguments_checker(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;
    return;
}

MentalResult attach_info_to_structure(const void* pInfo, const void* pStructure, size_t fieldOffset)
{
    if (pInfo == null || pStructure == null) return MENTAL_RESULT_POINTER_IS_NULL;
    
    unsigned char* pStructBytes = (unsigned char*)pStructure;
    void** ppInfoField = (void**)(pStructBytes + fieldOffset);

    if (*ppInfoField != null) return MENTAL_RESULT_POINTER_IS_NOT_NULL;

    *ppInfoField = (void*)pInfo;

    return MENTAL_RESULT_OK;
}
