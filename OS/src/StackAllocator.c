#include "StackAllocator.h"
#include "Error.h"
#include <stdio.h>

#define STACKALLOCATOR_ALIGNMENT 16

typedef struct StackAllocator
{
    uintptr_t pBottom;
    uintptr_t pLevel;
    uintptr_t pTop; 
}StackAllocator;

StackAllocator_Handle globalAllocator = NULL;

static uintptr_t StackAllocator_calculateNextLevel(uintptr_t in, size_t size);

extern StackAllocator_Handle StackAllocator_create(Memory_Handle heap)
{
    StackAllocator_Handle handle = NULL;

    if(NULL == heap)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    if(sizeof(StackAllocator) > Memory_getSize(heap))
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }

    handle = (StackAllocator_Handle) StackAllocator_calculateNextLevel(
        (uintptr_t)Memory_access(heap) + Memory_getSize(heap), sizeof(StackAllocator));
    handle->pBottom = (uintptr_t)handle;
    handle->pLevel = handle->pBottom;
    handle->pTop = (uintptr_t)Memory_access(heap);
    
    return handle;
}

extern void* StackAllocator_allocate(StackAllocator_Handle handle, size_t size)
{
    void* result = NULL;
    uintptr_t temp = 0;

    if(NULL == handle)
    {
        if(NULL == globalAllocator)
        {
            Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
        }

        handle = globalAllocator;
    }

    if(0 == size)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }

    temp = StackAllocator_calculateNextLevel(handle->pLevel, size);

    if(temp < handle->pTop)
    {
        Error_set(RESULT_FAILED_ALLOC);
    }
    else
    {
        handle->pLevel = temp;
        result = (void*) handle->pLevel;
    }

    return result;
}

extern Result StackAllocator_createGlobalAllocator(Memory_Handle globalHeap)
{
    Result result = RESULT_OK;

    globalAllocator = StackAllocator_create(globalHeap);

    if(NULL == globalAllocator)
    {
        Error_set(RESULT_INVALID_HANDLE);
    }

    return result;
}

static uintptr_t StackAllocator_calculateNextLevel(uintptr_t in, size_t size)
{
    uintptr_t temp = 0;
    temp = in - size;
    temp -= temp % STACKALLOCATOR_ALIGNMENT;
    return temp;
}



