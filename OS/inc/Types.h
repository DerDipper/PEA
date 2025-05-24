#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "Result.h"

typedef uint64_t duration;
typedef uint64_t timestamp;

typedef void* Generic_Handle;
typedef void (*Generic_Function)(Generic_Handle);
typedef bool (*Generic_Comparison)(Generic_Handle, Generic_Handle);
typedef Result (*Generic_Initialisation)(Generic_Handle);


