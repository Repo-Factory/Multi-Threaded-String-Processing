#pragma once
#include "types.hpp"
struct LineQueue
{

};

namespace ReadLines
{
    void* readlines(void* testFile);
    Success readLinesIntoQueue(LineQueue& lineQueue);
}

