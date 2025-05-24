#pragma once

#include "Types.h"

typedef struct NamedQueue_Config
{
    char* path;
    size_t size;
    size_t elementSize;
}NamedQueue_Config;


extern Result NamedQueue_create(NamedQueue_Config *pConfig);
