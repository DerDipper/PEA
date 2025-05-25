#include "PlatformConfig.h"
#include "Scheduler.h"
#include "StackAllocator.h"
#include "DeviceManager.h"

uint8_t mem[16*1024];

Memory globalStackAllocatorMemory = 
{
    .pData = mem,
    .size = sizeof(mem),
};

Scheduler_Config globalSchedulerConfig = 
{
    .cycleTime = 50000,
};

PlatformConfig_Descriptor OS_Scheduler_Config_Desc = 
{
    .type = PLATFORM_CONFIG_TYPE_OS_SCHEDULER,
    .config = &globalSchedulerConfig,
    .configurator = (Generic_Initialisation)Scheduler_createGlobalScheduler,
};

PlatformConfig_Descriptor OS_StackAllocator_Config_Desc = 
{
    .type = PLATFORM_CONFIG_TYPE_OS_ALLOCATOR,
    .config = &globalStackAllocatorMemory,
    .configurator = (Generic_Initialisation)StackAllocator_createGlobalAllocator,
};

PlatformConfig_Descriptor OS_DeviceManager_Config_Desc = 
{
    .type = PlATFORM_CONFIG_TYPE_OS_DEVICE_MANAGER,
    .config = NULL,
    .configurator = (Generic_Initialisation)DeviceManager_init,
};



