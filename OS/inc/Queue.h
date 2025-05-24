#pragma once

#include "Types.h"
#include "Memory.h"

typedef struct Queue_Config
{
    size_t elementCount;
    size_t elementSize;
    bool hasBlockingPush;
    bool hasBlockingPop;
    bool isFullyDynamic;
}Queue_Config;

typedef struct Queue_Config* Queue_Config_Handle;

extern const size_t QUEUE_OBJECT_SIZE;
typedef struct Queue* Queue_Handle;

extern Queue_Handle Queue_create(Queue_Config_Handle config);

extern Result Queue_push(Queue_Handle handle, Memory_Handle toStore);

extern Result Queue_pop(Queue_Handle handle, Memory_Handle toRead);

