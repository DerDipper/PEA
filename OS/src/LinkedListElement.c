#include "LinkedListElement.h"
#include "Error.h"
#include "Allocator.h"

#include <stdio.h>

typedef struct LinkedListElement
{
    Memory_Handle memory;
    LinkedListElement_Handle pNext;
}LinkedListElement;

extern LinkedListElement_Handle LinkedListElement_create(Memory_Handle relatedMemory)
{
    LinkedListElement_Handle handle = NULL;

    if(NULL == relatedMemory)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, NULL);
    }

    handle = Allocator_allocate(sizeof(LinkedListElement));

    if(NULL != handle)
    {
        handle->memory = relatedMemory;
        handle->pNext = NULL;
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
    }

    return handle;
}

extern Memory_Handle LinkedListElement_getMemory(LinkedListElement_Handle handle)
{
    Memory_Handle toReturn = NULL;
    
    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    toReturn = handle->memory;

    return toReturn;
}

extern Result LinkedListElement_attach(LinkedListElement_Handle toAttachto, LinkedListElement_Handle toAttach)
{
    Result toReturn = RESULT_OK;

    if(NULL == toAttachto)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(NULL == toAttach)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(Memory_getSize(toAttach->memory) != Memory_getSize(toAttachto->memory))
    {
        Error_setAndReturn(RESULT_SIZE_MISMATCH, RESULT_SIZE_MISMATCH);
    }

    toAttachto->pNext = toAttach;

    return toReturn;
}

extern LinkedListElement_Handle LinkedListElement_getAttached(LinkedListElement_Handle handle)
{
    LinkedListElement_Handle toReturn = NULL;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    toReturn = handle->pNext;

    return toReturn;
}

extern Result LinkedListElement_detach(LinkedListElement_Handle handle)
{
    Result toReturn = RESULT_OK; 

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    handle->pNext = NULL;

    return toReturn;
}

