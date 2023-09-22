#include "parent_thread.hpp"
#include <array>

std::array<pthread_t*, NUM_CHILD_THREADS> ParentThread::spawnWorkerThreads(const ThreadData* threadData[], const int numThreads)
{
    std::array<pthread_t*, NUM_CHILD_THREADS> threads;
    for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
    {
        threads[i] = new pthread_t;
        threads[i] = Threading::spawnThread(threadData[i]->threadFunction, threadData[i]->threadArgs);
    }
    return threads;
}