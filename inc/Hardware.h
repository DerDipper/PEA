#pragma once

#include "Types.h"

typedef struct Hardware_Config* Hardware_Config_Handle;

extern void Hardware_init(Hardware_Config_Handle);

extern Generic_Handle Hardware_getChannel(const uint32_t channel);

