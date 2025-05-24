#include "Memory.h"

#include "Allocator.h"
#include "Error.h"

#include <string.h>

typedef struct Memory
{
    void* pData;
    size_t size;
}Memory;

const size_t MEMORY_OBJECT_SIZE = sizeof(Memory);


Memory_Handle Memory_create(const size_t size)
{
    Memory_Handle handle = NULL;

    if(0 == size)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }

    handle = Allocator_allocate(sizeof(Memory));

    if(NULL != handle)
    {
        handle->pData = Allocator_allocate(size);
        if(NULL == handle->pData)
        {
            Error_set(RESULT_FAILED_ALLOC);
            handle = NULL;
        }
        else
        {
            handle->size = size;
        }
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
    }
    return handle;
}

Memory_Handle Memory_createFromObject(void* pRegion, const size_t size)
{
    Memory_Handle handle = NULL;

    if(NULL == pRegion)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, NULL);
    }
    if(0 == size)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }

    handle = Allocator_allocate(sizeof(Memory));

    if(NULL != handle)
    {
        handle->pData = pRegion;
        handle->size = size;
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
    }

    return handle;
}

Result Memory_createFromObjectLocally(void* pRegion, const size_t size, Memory_Handle handle)
{
    Result toReturn = RESULT_OK;

    if(NULL == pRegion)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, RESULT_NULL_POINTER);
    }
    if(0 == size)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, RESULT_INVALID_SIZE);
    }
    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, RESULT_NULL_POINTER);
    }
#if 0
    if(0 != handle->size)
    {
        Error_setAndReturn(RESULT_INVALID_OBJECT_STATE, RESULT_INVALID_OBJECT_STATE);
    }
    if(NULL != handle->pData)
    {
        Error_setAndReturn(RESULT_INVALID_OBJECT_STATE, RESULT_INVALID_OBJECT_STATE);
    }
#endif
    handle->pData = pRegion;
    handle->size = size;

    return toReturn;
}

void* Memory_access(Memory_Handle handle)
{
    void* address = NULL;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    address = handle->pData;

    return address;
}

void* Memory_accessAt(Memory_Handle handle, size_t position)
{
    void* address = NULL;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    if(position >= handle->size)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    address = ((uint8_t*)handle->pData) + position;

    return address;
}

size_t Memory_getSize(Memory_Handle handle)
{
    size_t size = 0;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, 0);
    }

    size = handle->size;

    return size;
}

Result Memory_set(Memory_Handle to, Memory_Handle from)
{
    Result res = RESULT_SIZE_MISMATCH; 

    if(NULL == to)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(NULL == from)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(to->size == from->size)
    {
        memcpy(to->pData, from->pData, to->size);
        res = RESULT_OK;
    }

    return res;
}

Result Memory_setFromRegion(Memory_Handle to, void* pData, size_t size)
{
    Result res = RESULT_SIZE_MISMATCH; 

    if(NULL == to)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(NULL == pData)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, RESULT_NULL_POINTER);
    }

    if(to->size != size)
    {
        Error_setAndReturn(RESULT_SIZE_MISMATCH, RESULT_SIZE_MISMATCH);
    }

    memcpy(to->pData, pData, to->size);
    res = RESULT_OK;

    return res;
}



