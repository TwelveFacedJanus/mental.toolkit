// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "mental.h"
#include <stddef.h>
#include "../utils/common.h"

MentalResult mentalCreateApplication(MentalApplication *pApplication)
{
    if (pApplication->pInfo == null ) return MENTAL_RESULT_POINTER_IS_NULL;

    return MENTAL_RESULT_OK;
}

