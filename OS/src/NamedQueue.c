#include "NamedQueue.h"
#include "Queue.h"
#include "DeviceManager.h"
#include <alloca.h>
#include <stdio.h>

static Result NamedQueue_write(Generic_Handle handle, void *buf, size_t size)
{
    Memory_Handle mem = alloca(MEMORY_OBJECT_SIZE);
    Memory_createFromObjectLocally(buf, size, mem);
    Queue_push(handle, mem);

    return RESULT_OK;
}

static Result NamedQueue_read(Generic_Handle handle, void *buf, size_t size)
{
    Memory_Handle mem = alloca(MEMORY_OBJECT_SIZE);
    Memory_createFromObjectLocally(buf, size, mem);
    Queue_pop(handle, mem);

    return RESULT_OK;
}

extern Result NamedQueue_create(NamedQueue_Config *pConfig)
{
    Queue_Config config = {.elementCount = 0,
                           .elementSize = 0,
                           .hasBlockingPop = false,
                           .hasBlockingPush = false,
                           .isFullyDynamic = false};

    DeviceManager_Descriptor desc = {.path = NULL,
                                     .flags = 0,
                                     .interface =
                                         {
                                             .onClose = NULL,
                                             .onFlush = NULL,
                                             .onIoctl = NULL,
                                             .onOpen = NULL,
                                             .onRead = NamedQueue_read,
                                             .onWrite = NamedQueue_write,
                                         }};
    if (NULL != pConfig)
    {
        config.elementCount = pConfig->size;
        config.elementSize = pConfig->elementSize;
        desc.path = pConfig->path;

        Queue_Handle queue = Queue_create(&config);
        DeviceManager_register(queue, &desc);
    }

    return RESULT_OK;
}
