#pragma once

#include "Types.h"
#include "Memory.h"

typedef struct StackAllocator* StackAllocator_Handle;

extern Result StackAllocator_createGlobalAllocator(Memory_Handle heap);
extern StackAllocator_Handle StackAllocator_create(Memory_Handle heap);

extern void* StackAllocator_allocate(StackAllocator_Handle handle, size_t size);



