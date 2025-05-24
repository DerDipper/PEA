#pragma once

#include <stdlib.h>
#include "StackAllocator.h"

#define USE_STACKALLOCATOR

#ifdef USE_STACKALLOCATOR
#define Allocator_allocate(X) StackAllocator_allocate(NULL, (X))
#else
#define Allocator_allocate(X) malloc((X))
#endif


