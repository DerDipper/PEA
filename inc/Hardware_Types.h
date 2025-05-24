#pragma once

#include "Types.h"

typedef enum Hardware_Type
{
    HARDWARE_TYPE_GPIO,
    HARDWARE_TYPE_GPIO_GROUP,
    HARDWARE_TYPE_UART,
    HARDWARE_TYPE_I2C,
    HARDWARE_TYPE_SPI,
    HARDWARE_TYPE_RTC,
}Hardware_Type;

typedef struct Hardware_Descriptor
{
    Hardware_Type type;
}Hardware_Descriptor;


