#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>
#include <functional>
#include <atomic>

typedef void* (*ThreadFunction)(void*);

namespace Threading
{
    pthread_t* spawnThread(ThreadFunction function, void* args);
    void waitForCondition(std::atomic<bool>* condition);
    void safeAction(pthread_mutex_t* mutex, std::function<void()> action);
}

#endif