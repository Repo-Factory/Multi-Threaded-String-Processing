#pragma once
#include <pthread.h>
#include <functional>
#include <atomic>

typedef void* (*ThreadFunction)(void*);

struct PthreadData
{
    pthread_mutex_t mutex;
    pthread_cond_t condition;
};

namespace Threading
{
    pthread_t* spawnThread(ThreadFunction function, void* args);
    void waitForCondition(std::atomic<bool>* condition);
    void safeAction(pthread_mutex_t* mutex, std::function<void()> action);
}
