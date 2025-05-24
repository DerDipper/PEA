#pragma once

#include "Types.h"

extern Generic_Handle open(char* lookup);

extern Result write(Generic_Handle handle, void* buf, size_t size);

extern Result read(Generic_Handle handle, void *buf, size_t size);

extern Result close(Generic_Handle handle);

extern Result flush(Generic_Handle handle);

extern Result ioctl(Generic_Handle handle, uint32_t request, void* arg);

