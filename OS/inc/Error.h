#pragma once

#include "Types.h"

#define Error_set(X)  (ErrorStorage_result = (X))
#define Error_setAndReturn(X,Y) ErrorStorage_result = (X); return (Y);
#define Error_get() (ErrorStorage_result)

extern Result ErrorStorage_result;