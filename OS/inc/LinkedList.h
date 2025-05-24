#pragma once

#include "Types.h"
#include "LinkedListElement.h"

typedef struct LinkedList* LinkedList_Handle;

extern LinkedList_Handle LinkedList_create(const size_t elementSize);

extern Result LinkedList_pushBack(LinkedList_Handle handle, LinkedListElement_Handle toPush);

extern Result LinkedList_pushFront(LinkedList_Handle handle, LinkedListElement_Handle toPush);

extern LinkedListElement_Handle LinkedList_popFront(LinkedList_Handle handle);

extern bool LinkedList_hasElements(LinkedList_Handle handle);

extern LinkedListElement_Handle LinkedList_findFirst(LinkedList_Handle handle, Generic_Comparison comparison, Generic_Handle object);

extern Result LinkedList_insertBefore(LinkedList_Handle handle, LinkedListElement_Handle insertBefore, LinkedListElement_Handle toInsert);

extern LinkedListElement_Handle LinkedList_peek(LinkedList_Handle handle);

extern Result LinkedList_rotate(LinkedList_Handle handle);


