#pragma once
#include <pthread.h>
#include <functional>

typedef void* (*ThreadFunction)(void*);

struct Signal
{

};

struct PthreadData
{
    pthread_mutex_t mutex;
    pthread_cond_t condition;
};

namespace Threading
{
    bool waitForThread(Signal& signal);
    pthread_t* spawnThread(ThreadFunction function, void* args);
    void safeAction(pthread_mutex_t& mutex, std::function<void()>& action);
}
