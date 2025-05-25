#include "Scheduler.h"
#include "LinkedList.h"
#include "Allocator.h"
#include "Error.h"
#include "Time.h"

typedef struct Scheduler_Executer
{
    Generic_Handle object;
    Generic_Function taskFunc;
} Scheduler_Executer;

typedef struct Scheduler_Timing
{
    uint64_t startTime;
    uint64_t duration;
} Scheduler_Timing;

typedef struct Scheduler_Entry
{
    Scheduler_Executer what;
    Scheduler_Timing when;
} Scheduler_Entry;

typedef struct Scheduler
{
    Scheduler_Config_Handle config;
    LinkedList_Handle jobList;
} Scheduler;

static void Scheduler_prepare(Scheduler_Handle handle);
static Result Scheduler_executeInternal(Scheduler_Handle handle);

static Scheduler_Handle globalScheduler = NULL;

extern Result Scheduler_createGlobalScheduler(Scheduler_Config_Handle config)
{
    globalScheduler = Scheduler_create(config);
    return RESULT_OK;
}

extern Scheduler_Handle Scheduler_create(Scheduler_Config_Handle config)
{
    Scheduler_Handle handle = NULL;

    if (NULL == config)
    {
        Error_setAndReturn(RESULT_NULL_POINTER, NULL);
    }

    handle = Allocator_allocate(sizeof(Scheduler));

    if (NULL != handle)
    {
        handle->jobList = LinkedList_create(sizeof(Scheduler_Entry));
        handle->config = config;
    }
    else
    {
        Error_set(RESULT_NULL_POINTER);
    }

    return handle;
}

static bool Compare_Scheduler_Entry(Scheduler_Entry *a, Scheduler_Entry *b)
{
    if (a->when.duration + a->when.startTime <= b->when.startTime)
    {
        return true;
    }

    return false;
}

extern Result Scheduler_addTask(Scheduler_Handle handle, Scheduler_Task_Handle task)
{
    Result toReturn = RESULT_OK;
    Scheduler_Entry entry;
    if (NULL == handle)
    {
        handle = globalScheduler;
    }

    if (NULL == task)
    {
        Error_setAndReturn(RESULT_INVALID_HANDLE, RESULT_INVALID_HANDLE);
    }

    Memory_Handle jobEntry = alloca(MEMORY_OBJECT_SIZE);
    Memory_createFromObjectLocally(&entry, sizeof(entry), jobEntry);
    entry.what.object = task->object;
    entry.what.taskFunc = task->taskFunc;
    entry.when.duration = task->duration;

    for (timestamp t = task->phase;
         t < handle->config->cycleTime;
         t += task->period)
    {
        LinkedListElement_Handle toAdd = LinkedListElement_create(Memory_create(sizeof(Scheduler_Entry)));
        Scheduler_Entry *pEntry = Memory_access(LinkedListElement_getMemory(toAdd));

        *pEntry = entry;
        pEntry->when.startTime = t;

        if (LinkedList_hasElements(handle->jobList))
        {
            LinkedListElement_Handle elem = LinkedList_findFirst(handle->jobList, (Generic_Comparison)Compare_Scheduler_Entry, pEntry);
            if (NULL == elem)
            {
                LinkedList_pushBack(handle->jobList, toAdd);
            }
            else
            {
                LinkedList_insertBefore(handle->jobList, elem, toAdd);
            }
        }
        else
        {
            LinkedList_pushBack(handle->jobList, toAdd);
        }
    }

    return toReturn;
}

extern Result Scheduler_execute(Scheduler_Handle handle)
{
    Result toReturn = RESULT_OK;

    if(NULL == handle)
    {
        handle = globalScheduler;
    }

    Scheduler_prepare(handle);
    toReturn = Scheduler_executeInternal(handle);

    return toReturn;
}

// makes jobs relative to each other rather than to a time schedule
static void Scheduler_prepare(Scheduler_Handle handle)
{
    timestamp t0 = 0;
    timestamp t1 = 0;
    LinkedListElement_Handle firstEntry = LinkedList_peek(handle->jobList);
    LinkedListElement_Handle prepareEntry = firstEntry;
    do
    {
        Scheduler_Entry* prepare = Memory_access( LinkedListElement_getMemory(prepareEntry) );
        t1 = prepare->when.startTime;
        prepare->when.startTime -= t0;
        t0 = t1;
        LinkedList_rotate(handle->jobList);
        prepareEntry = LinkedList_peek(handle->jobList);
    }while(prepareEntry != firstEntry);
    
    //first element also has time relative to last element
    Scheduler_Entry* prepare = Memory_access( LinkedListElement_getMemory(prepareEntry) );
    prepare->when.startTime += handle->config->cycleTime - t0;
}

static Result Scheduler_executeInternal(Scheduler_Handle handle)
{

    Result toReturn = RESULT_EMPTY;

    timestamp t0 = Time_getTimestamp();
    while(LinkedList_hasElements(handle->jobList))
    {

        LinkedListElement_Handle entry = LinkedList_peek(handle->jobList);
        Scheduler_Entry* pEntry = Memory_access( LinkedListElement_getMemory(entry) );

        while(pEntry->when.startTime > Time_elapsedSince(t0))
        {
            ;
        }

        t0 = Time_getTimestamp();

        pEntry->what.taskFunc(pEntry->what.object);
        timestamp deltaTime = Time_elapsedSince(t0);
        LinkedList_rotate(handle->jobList);

        if(deltaTime > pEntry->when.duration)
        {
            Error_set(RESULT_TIME_ELAPSED);
            toReturn = RESULT_TIME_ELAPSED;
            break;
        }

    }

    return toReturn;
}


