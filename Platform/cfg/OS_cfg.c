#include "PlatformConfig.h"
#include "Scheduler.h"

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

