#include "Result.h"
#include "Types.h"

extern char* Result_to_string(Result result)
{
    char* toReturn = NULL;

    switch (result)
    {
        case RESULT_OK: toReturn = "RESULT_OK"; break;
        case RESULT_INVALID_HANDLE: toReturn = "RESULT_INVALID_HANDLE"; break;
        case RESULT_SIZE_MISMATCH: toReturn = "RESULT_SIZE_MISMATCH"; break;
        case RESULT_INVALID_SIZE: toReturn = "RESULT_INVALID_SIZE"; break;
        case RESULT_FAILED_ALLOC: toReturn = "RESULT_FAILED_ALLOC"; break;
        case RESULT_NULL_POINTER: toReturn = "RESULT_NULL_POINTER"; break;
        case RESULT_INVALID_OBJECT_STATE: toReturn = "RESULT_INVALID_OBJECT_STATE"; break;
        case RESULT_UNSUPPORTED: toReturn = "RESULT_UNSUPPORTED"; break;
        case RESULT_EMPTY: toReturn = "RESULT_EMPTY"; break;
        case RESULT_FULL: toReturn = "RESULT_FULL"; break;
        case RESULT_NOT_FOUND: toReturn = "RESULT_NOT_FOUND"; break;    
    default:
        break;
    }

    return toReturn;

}