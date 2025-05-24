#include "NamedQueue.h"
#include "PlatformConfig.h"


static NamedQueue_Config VectorQueue_Config = {
    .path = "/ipc/VectorQueue",
    .size = 10,
    .elementSize = 4,
};

PlatformConfig_Descriptor vectorQueue_Config_Desc = 
{
    .type = PLATFORM_CONFIG_TYPE_NAMEDQUEUE,
    .config = &VectorQueue_Config,
    .configurator = (Generic_Initialisation)NamedQueue_create,
};



