#include "Queue.h"
#include "LinkedList.h"
#include "Error.h"
#include "Allocator.h"

typedef struct Queue
{
    LinkedList_Handle qList;
    LinkedList_Handle elemList;
    Queue_Config_Handle config;
}Queue;

const size_t QUEUE_OBJECT_SIZE = sizeof(Queue);

extern Queue_Handle Queue_create(Queue_Config_Handle config)
{
    Queue_Handle handle = NULL;
    if(NULL == config)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, NULL);
    }
    if(0 == config->elementCount && false == config->isFullyDynamic)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }
    if(0 != config->elementCount && true == config->isFullyDynamic)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }
    if(0 == config->elementSize)
    {
        Error_setAndReturn(RESULT_INVALID_SIZE, NULL);
    }

    if(true == config->hasBlockingPop)
    {
        Error_setAndReturn(RESULT_UNSUPPORTED, NULL);
    }
    if(true == config->hasBlockingPush)
    {
        Error_setAndReturn(RESULT_UNSUPPORTED, NULL);
    }

    if(true == config->isFullyDynamic)
    {
        Error_setAndReturn(RESULT_UNSUPPORTED, NULL);
    }

    handle = Allocator_allocate(sizeof(Queue));

    if(NULL != handle)
    {
        handle->config = config;
        handle->qList = LinkedList_create(config->elementSize);

        if(false == config->isFullyDynamic)
        {
            handle->elemList = LinkedList_create(config->elementSize);

            for(size_t i = 0; i < handle->config->elementCount; i++)
            {
                Memory_Handle mem = Memory_create(handle->config->elementSize);
                LinkedListElement_Handle toPut = LinkedListElement_create(mem);
                LinkedList_pushFront(handle->elemList, toPut);
            }
        }
        else
        {
            handle->elemList = NULL;
        }
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
    }

    return handle;
}

extern Result Queue_push(Queue_Handle handle, Memory_Handle toStore)
{
    Result toReturn = RESULT_OK;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(NULL == toStore)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(LinkedList_hasElements(handle->elemList))
    {
        LinkedListElement_Handle elem = LinkedList_popFront(handle->elemList);
        Memory_set(LinkedListElement_getMemory(elem), toStore);
        LinkedList_pushBack(handle->qList, elem); 
    }
    else
    {
        Error_set(RESULT_FULL);
        toReturn = RESULT_FULL;
    }

    return toReturn;
}

extern Result Queue_pop(Queue_Handle handle, Memory_Handle toRead)
{
    Result toReturn = RESULT_OK;

    if(NULL == handle)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(NULL == toRead)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    if(LinkedList_hasElements(handle->qList))
    {
        LinkedListElement_Handle elem = LinkedList_popFront(handle->qList);
        Memory_set(toRead, LinkedListElement_getMemory(elem));
        LinkedList_pushBack(handle->elemList, elem); 
    }
    else
    {
        Error_set(RESULT_EMPTY);
        toReturn = RESULT_EMPTY;
    }

    return toReturn;
}