#ifndef MENTAL_COMMON_H
#define MENTAL_COMMON_H

#include "../core/mental.h"


void arguments_checker(int argc, const char* argv[]);
MentalResult attach_info_to_structure(const void* pInfo, const void* pStructure, size_t fieldOffset);

#endif // MENTAL_COMMON_H
