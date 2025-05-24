#pragma once

#include "Types.h"
#include "Memory.h"

typedef struct LinkedListElement* LinkedListElement_Handle;

extern LinkedListElement_Handle LinkedListElement_create(Memory_Handle relatedMemory);

extern Memory_Handle LinkedListElement_getMemory(LinkedListElement_Handle handle);

extern Result LinkedListElement_attach(LinkedListElement_Handle toAttachto, LinkedListElement_Handle toAttach);

extern LinkedListElement_Handle LinkedListElement_getAttached(LinkedListElement_Handle handle);

extern Result LinkedListElement_detach(LinkedListElement_Handle handle);

