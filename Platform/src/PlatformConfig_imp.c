#include "PlatformConfig_imp.h"

PlatformConfig_Descriptor const * const PlatformConfig_config[] = 
{
    &OS_StackAllocator_Config_Desc,
    &OS_Scheduler_Config_Desc,
    &OS_DeviceManager_Config_Desc,
    &vectorQueue_Config_Desc,
    NULL,
};

