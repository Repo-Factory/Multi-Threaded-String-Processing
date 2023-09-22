#include "threading.hpp"
#include "types.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <chrono>

#define THREAD_CREATION_SUCCESS(threadReturn) threadReturn==0
#define THREAD_CREATION_MESSAGE "Thread Not Created Properly"

void Threading::safeAction(pthread_mutex_t* mutex, std::function<void()> performAction)
{
    pthread_mutex_lock(mutex);
    performAction();
    pthread_mutex_unlock(mutex);
}

void Threading::waitForCondition(std::atomic<bool>* condition)
{
    while (!*condition) std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

pthread_t* Threading::spawnThread(ThreadFunction function, void* args)
{
    pthread_t* thread = new pthread_t;
    pthread_create(thread, NULL, function, args);
    return thread;
}
