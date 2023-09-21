#include "threading.hpp"
#include "types.hpp"
#include <stdio.h>
#include <stdlib.h>

#define THREAD_CREATION_SUCCESS(threadReturn) threadReturn==0
#define THREAD_CREATION_MESSAGE "Thread Not Created Properly"

void Threading::safeAction(pthread_mutex_t& mutex, std::function<void()>& performAction)
{
    pthread_mutex_lock(&mutex);
    performAction();
    pthread_mutex_unlock(&mutex);
}

PthreadData* initPthreadData(PthreadData* pthread_data)
{
    pthread_mutex_init(&pthread_data->mutex, NULL);
    pthread_cond_init(&pthread_data->condition, NULL);
    return pthread_data;
}

Success destroyPthreadData(PthreadData* pthread_data)
{
    pthread_mutex_destroy(&pthread_data->mutex);
    pthread_cond_destroy(&pthread_data->condition);
    return Success{true};
}

pthread_t* Threading::spawnThread(ThreadFunction function, void* args)
{
    pthread_t* thread = new pthread_t;
    pthread_create(thread, NULL, function, args);
    return thread;
}

// pthread_cond_wait(&mutex, &cond);
// pthread_cond_signal(&cond);
