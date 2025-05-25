#pragma once

#include "Types.h"

typedef enum PlatformConfig_Type
{
    PLATFORM_CONFIG_TYPE_OS = 0x00000000,
    PLATFORM_CONFIG_TYPE_OS_ALLOCATOR,
    PLATFORM_CONFIG_TYPE_OS_SCHEDULER,
    PlATFORM_CONFIG_TYPE_OS_DEVICE_MANAGER,
    PLATFORM_CONFIG_TYPE_HARDWARE = 0x10000000,
    PLATFORM_CONFIG_TYPE_MCU,
    PLATFORM_CONFIG_TYPE_PINMUX,
    PLATFORM_CONFIG_TYPE_GPIO,
    PLATFORM_CONFIG_TYPE_DEVICE = 0x20000000,
    PLATFORM_CONFIG_TYPE_IAC = 0x30000000,
    PLATFORM_CONFIG_TYPE_NAMEDQUEUE,
    PLATFORM_CONFIG_TYPE_APP = 0x40000000,
    /********
     * Application Specific Types
     *****/
}PlatformConfig_Type;

typedef struct PlatformConfig_Descriptor
{
    PlatformConfig_Type type;
    Generic_Handle config;
    Generic_Initialisation configurator;
}PlatformConfig_Descriptor;

extern PlatformConfig_Descriptor const * const PlatformConfig_config[];
