#ifndef MENTAL_REQUESTS_H
#define MENTAL_REQUESTS_H

#include "../core/mental.h"

typedef enum MentalRequestType {
    MENTAL_REQUEST_TYPE_POST = 0,
    MENTAL_REQUEST_TYPE_GET = 1,
    MENTAL_REQUEST_TYPE_DELETE = 2,
    MENTAL_REQUEST_TYPE_PATCH = 3,
    MENTAL_REQUEST_TYPE_PUT = 4,
} MentalRequestType;

typedef struct MentalRequestData {
    MentalStructureType eType;
    MentalRequestType   eRtype;
    char* url;
} MentalRequestData;

MentalResult mentalRequest(MentalRequestData *pData);


#endif // MENTAL_REQUESTS_H
