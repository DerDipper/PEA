#pragma once

#include "Types.h"

typedef Result (*open_if)(Generic_Handle handle);

typedef Result (*write_if)(Generic_Handle handle, void* buf, size_t size);

typedef Result (*read_if)(Generic_Handle handle, void *buf, size_t size);

typedef Result (*close_if)(Generic_Handle handle);

typedef Result (*flush_if)(Generic_Handle handle);

typedef Result (*ioctl_if)(Generic_Handle handle, uint32_t request, void* arg);

typedef struct Device_Interface
{
    open_if onOpen;
    write_if onWrite;
    read_if onRead;
    close_if onClose;
    flush_if onFlush;
    ioctl_if onIoctl;
}Device_Interface;

typedef struct DeviceManager_Descriptor
{
    const char* path;
    uint32_t flags;
    Device_Interface interface;
}DeviceManager_Descriptor;

extern Result DeviceManager_init(void);

extern Result DeviceManager_register(Generic_Handle handle, DeviceManager_Descriptor* desc);


