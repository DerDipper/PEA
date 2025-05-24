#pragma once 

#include "Types.h"
#include <stdio.h>

typedef struct Scheduler_Task
{
    uint64_t phase;
    uint64_t period;
    uint64_t duration;
    Generic_Handle object;
    Generic_Function taskFunc;
}Scheduler_Task;

typedef struct Scheduler_Config
{
    uint64_t cycleTime;
}Scheduler_Config;

typedef struct Scheduler_Task* Scheduler_Task_Handle;

typedef struct Scheduler_Config* Scheduler_Config_Handle;

typedef struct Scheduler* Scheduler_Handle;

extern Scheduler_Handle Scheduler_create(Scheduler_Config_Handle config);

extern Result Scheduler_addTask(Scheduler_Handle handle, Scheduler_Task_Handle task);

extern Result Scheduler_execute(Scheduler_Handle handle);





