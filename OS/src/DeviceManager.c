#include "DeviceManager.h"
#include "Allocator.h"
#include "LinkedList.h"
#include "Error.h"
#include <string.h>


typedef struct DeviceManager* DeviceManager_Handle;
typedef struct Device* Device_Handle;

typedef struct DeviceManager
{
    LinkedList_Handle Devices;
}DeviceManager;

typedef struct Device
{
    DeviceManager_Descriptor* pDesc;
    Generic_Handle handle;
}Device;

DeviceManager_Handle devMan = NULL;

extern Result DeviceManager_init(void)
{
    Result toReturn = RESULT_OK;
    DeviceManager_Handle handle = Allocator_allocate(sizeof(DeviceManager));

    if(NULL != handle)
    {
        Error_set(RESULT_FAILED_ALLOC);
        handle->Devices = LinkedList_create(sizeof(Device));
        if(NULL == handle->Devices)
        {
            Error_set(RESULT_FAILED_ALLOC);
            toReturn = RESULT_FAILED_ALLOC;
        }
        else
        {
            devMan = handle;
        }
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
        toReturn = RESULT_FAILED_ALLOC;
    }

    return toReturn;
}

extern Result DeviceManager_register(Generic_Handle handle, DeviceManager_Descriptor* desc)
{
    Memory_Handle mem = Memory_create(sizeof(Device));
    Device_Handle dev = Memory_access(mem);

    if(NULL != dev)
    {
        dev->handle = handle;
        dev->pDesc = desc;
        LinkedList_pushBack( devMan->Devices, LinkedListElement_create(mem));
    }
    else
    {
        Error_set(RESULT_FAILED_ALLOC);
    }

    return RESULT_OK;
}

static bool isDevicePathEqual(char* lookup, Device_Handle dev)
{
    if(0 == strcmp(lookup, dev->pDesc->path))
    {
        return true;
    }

    return false;
}

extern Generic_Handle open(char* lookup)
{
    LinkedListElement_Handle handle = LinkedList_findFirst(devMan->Devices, (Generic_Comparison)isDevicePathEqual, lookup);

    Device_Handle dev = NULL;

    if(NULL != handle)
    {
        dev =  Memory_access(LinkedListElement_getMemory(handle));

        if(NULL != dev)
        {
            if(NULL != dev->pDesc->interface.onOpen)
            {
                dev->pDesc->interface.onOpen(dev->handle);
            }
        }
    }

    return dev;
}

extern Result write(Generic_Handle handle, void* buf, size_t size)
{
    Device_Handle dev = handle;

    if(NULL != dev)
    {
        if(NULL != dev->pDesc->interface.onOpen)
        {
            dev->pDesc->interface.onWrite(dev->handle, buf, size);
        }
        else
        {
            return RESULT_UNSUPPORTED;
        }
    }
    else
    {
        return RESULT_INVALID_HANDLE;
    }

    return RESULT_OK;
}

extern Result read(Generic_Handle handle, void *buf, size_t size)
{
    Device_Handle dev = handle;

    if(NULL != dev)
    {
        if(NULL != dev->pDesc->interface.onOpen)
        {
            dev->pDesc->interface.onRead(dev->handle, buf, size);
        }
        else
        {
            return RESULT_UNSUPPORTED;
        }
    }
    else
    {
        return RESULT_INVALID_HANDLE;
    }

    return RESULT_OK;
}

extern Result close(Generic_Handle handle)
{
    Device_Handle dev = handle;

    if(NULL != dev)
    {
        if(NULL != dev->pDesc->interface.onOpen)
        {
            dev->pDesc->interface.onClose(dev->handle);
        }
    }
    else
    {
        return RESULT_INVALID_HANDLE;
    }

    return RESULT_OK;
}

extern Result flush(Generic_Handle handle)
{
   Device_Handle dev = handle;

    if(NULL != dev)
    {
        if(NULL != dev->pDesc->interface.onOpen)
        {
            dev->pDesc->interface.onFlush(dev->handle);
        }
        else
        {
            return RESULT_UNSUPPORTED;
        }
    }
    else
    {
        return RESULT_INVALID_HANDLE;
    }

    return RESULT_OK;
}

extern Result ioctl(Generic_Handle handle, uint32_t request, void* arg)
{
   Device_Handle dev = handle;

    if(NULL != dev)
    {
        if(NULL != dev->pDesc->interface.onOpen)
        {
            dev->pDesc->interface.onIoctl(dev->handle, request, arg);
        }
        else
        {
            return RESULT_UNSUPPORTED;
        }
    }
    else
    {
        return RESULT_INVALID_HANDLE;
    }

    return RESULT_OK;
}





