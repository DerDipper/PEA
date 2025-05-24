#pragma once

#include "Types.h"

extern const size_t MEMORY_OBJECT_SIZE;
typedef struct Memory* Memory_Handle;

extern Memory_Handle Memory_create(const size_t size);

extern Memory_Handle Memory_createFromObject(void* pRegion, const size_t size);

extern Result Memory_createFromObjectLocally(void* pRegion, const size_t size, Memory_Handle handle);

extern void* Memory_access(Memory_Handle handle);

extern void* Memory_accessAt(Memory_Handle handle, size_t position);

extern Result Memory_set(Memory_Handle to, Memory_Handle from);

extern Result Memory_setFromRegion(Memory_Handle to, void* pData, size_t size);

extern size_t Memory_getSize(Memory_Handle handle);

