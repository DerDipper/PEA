#include "Platform.h"
#include "PlatformConfig.h"
#include <stdio.h>

extern void Platform_Setup()
{
    uint8_t initStage = 0;
    
    while(initStage < 0xF0)
    {
        size_t i = 0;
        PlatformConfig_Descriptor const * it = PlatformConfig_config[i];
        while (NULL != it)
        {
            if(initStage ==(uint8_t)(it->type >> 24))
            {

                it->configurator(it->config);
            }
            i++;
            it = PlatformConfig_config[i];
        }
        initStage+=0x10;
    }
    return;
}


