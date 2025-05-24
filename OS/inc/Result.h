#pragma once

typedef enum
{
        RESULT_OK,
        RESULT_INVALID_HANDLE,
        RESULT_SIZE_MISMATCH,
        RESULT_INVALID_SIZE,
        RESULT_FAILED_ALLOC,
        RESULT_NULL_POINTER,
        RESULT_INVALID_OBJECT_STATE,
        RESULT_UNSUPPORTED,
        RESULT_TIME_ELAPSED,
        RESULT_EMPTY,
        RESULT_FULL,
        RESULT_NOT_FOUND,
}Result;

extern char* Result_to_string(Result result);

