#include "LinkedList.h"
#include "Error.h"
#include "Allocator.h"

#include <stdio.h>

typedef struct LinkedList
{
    LinkedListElement_Handle first;
    LinkedListElement_Handle last;
    size_t elementSize;
} LinkedList;

extern LinkedList_Handle LinkedList_create(const size_t elementSize)
{
    LinkedList_Handle handle = NULL;

    if (0 == elementSize)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }

    handle = Allocator_allocate(sizeof(LinkedList));

    if (NULL != handle)
    {
        handle->first = NULL;
        handle->last = NULL;
        handle->elementSize = elementSize;
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
    }

    return handle;
}

extern Result LinkedList_pushBack(LinkedList_Handle handle, LinkedListElement_Handle toPush)
{
    Result toReturn = RESULT_OK;

    if (NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if (NULL == toPush)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if (handle->elementSize != Memory_getSize(LinkedListElement_getMemory(toPush)))
    {
        Error_setAndReturn(RESULT_SIZE_MISMATCH, RESULT_SIZE_MISMATCH);
    }

    if (NULL == handle->first)
    {
        if (NULL != handle->last)
        {
            Error_setAndReturn(RESULT_INVALID_OBJECT_STATE, RESULT_INVALID_OBJECT_STATE);
        }
    }

    if (NULL == handle->first)
    {
        handle->first = handle->last = toPush;
    }
    else
    {
        toReturn = LinkedListElement_attach(handle->last, toPush);
    }

    if (RESULT_OK == toReturn)
    {
        handle->last = toPush;
    }

    return toReturn;
}

extern Result LinkedList_pushFront(LinkedList_Handle handle, LinkedListElement_Handle toPush)
{
    Result toReturn = RESULT_OK;

    if (NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if (NULL == toPush)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if (handle->elementSize != Memory_getSize(LinkedListElement_getMemory(toPush)))
    {
        Error_setAndReturn(RESULT_SIZE_MISMATCH, RESULT_SIZE_MISMATCH);
    }

    if (NULL == handle->first)
    {
        if (NULL != handle->last)
        {
            Error_setAndReturn(RESULT_INVALID_OBJECT_STATE, RESULT_INVALID_OBJECT_STATE);
        }
    }

    if (NULL == handle->first)
    {
        handle->first = handle->last = toPush;
    }
    else
    {
        toReturn = LinkedListElement_attach(toPush, handle->first);
    }

    if (RESULT_OK == toReturn)
    {
        handle->first = toPush;
    }

    return toReturn;
}

extern LinkedListElement_Handle LinkedList_popFront(LinkedList_Handle handle)
{
    LinkedListElement_Handle toReturn = NULL;

    if (NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    if (NULL == handle->first)
    {
        Error_setAndReturn(RESULT_EMPTY, NULL);
    }

    toReturn = handle->first;
    handle->first = LinkedListElement_getAttached(handle->first);

    if (NULL == handle->first)
    {
        if (toReturn == handle->last)
        {
            handle->last = NULL;
        }
        else
        {
            Error_set(RESULT_INVALID_OBJECT_STATE);
        }
    }

    return toReturn;
}

extern bool LinkedList_hasElements(LinkedList_Handle handle)
{
    bool toReturn = false;

    if (NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, false);
    }

    if (NULL != handle->first)
    {
        toReturn = true;
    }

    return toReturn;
}

extern LinkedListElement_Handle LinkedList_findFirst(LinkedList_Handle handle, Generic_Comparison comparison, Generic_Handle object)
{
    LinkedListElement_Handle found = NULL;

    if (NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    if (NULL == comparison)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, NULL);
    }

    if (NULL == object)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    if (NULL == handle->first)
    {
        Error_setAndReturn(RESULT_EMPTY, NULL);
    }

    LinkedListElement_Handle pWorker = handle->first;

    while (pWorker != handle->last)
    {
        if (true == comparison(object, Memory_access(LinkedListElement_getMemory(pWorker))))
        {
            found = pWorker;
            break;
        }
        pWorker = LinkedListElement_getAttached(pWorker);
    }

    if (true == comparison(object, Memory_access(LinkedListElement_getMemory(pWorker))))
    {
        found = pWorker;
    }

    return found;
}

extern Result LinkedList_insertBefore(LinkedList_Handle handle, LinkedListElement_Handle insertBefore, LinkedListElement_Handle toInsert)
{
    Result toReturn = RESULT_OK;

    if (NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }
    if (NULL == insertBefore)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }
    if (NULL == toInsert)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    LinkedListElement_Handle pWorker = handle->first;
    LinkedListElement_Handle prevWorker = handle->first;

    if (NULL == pWorker)
    {
        Error_set(RESULT_EMPTY);
        toReturn = RESULT_EMPTY;
    }
    else if ((insertBefore == pWorker) && (pWorker == handle->first))
    {
        LinkedList_pushFront(handle, toInsert);
    }
    else
    {
        while (pWorker != insertBefore)
        {
            prevWorker = pWorker;
            pWorker = LinkedListElement_getAttached(pWorker);
            if (prevWorker == handle->last)
            {
                Error_set(RESULT_NOT_FOUND);
                toReturn = RESULT_NOT_FOUND;
                break;
            }
        }

        if (RESULT_OK == toReturn)
        {
            LinkedListElement_attach(prevWorker, toInsert);
            LinkedListElement_attach(toInsert, pWorker);
        }
    }

    return toReturn;
}

extern LinkedListElement_Handle LinkedList_peek(LinkedList_Handle handle)
{
    LinkedListElement_Handle toReturn = NULL;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, NULL);
    }

    toReturn = handle->first;

    return toReturn;
}

extern Result LinkedList_rotate(LinkedList_Handle handle)
{
    Result result = RESULT_OK;

    LinkedListElement_Handle elem = LinkedList_popFront(handle);

    if(NULL != elem)
    {
        LinkedList_pushBack(handle, elem);
    }
    else
    {
        result = RESULT_EMPTY;
    }

    return result;
}



