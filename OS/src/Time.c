#include "Time.h"

#include <time.h>


extern timestamp Time_getTimestamp()
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

    timestamp t = time.tv_sec*1000000 + time.tv_nsec/1000;

    return t;
}

extern timestamp Time_elapsedSince(timestamp t)
{
    return Time_getTimestamp() - t;
}

