#define NUM_OF_FILES 2
#define VOCAB_FILE_INDEX 0
#define TEST_FILE_INDEX 1

#include <queue>
#include <cstdarg>
#include <string>
#include <functional>
#include "sys/types.h"
#include "types.hpp"
#include "progress_bar.hpp"
#include "threading.hpp"

struct ReadLinesData
{   
    const char* testfile_path;
    pthread_mutex_t* line_queue_mutex;
    pthread_cond_t* lines_read_cond;
    std::queue<std::string>* line_queue;
};

struct ReadVocabData
{
    const char* vocab_path;
    pthread_mutex_t* vocab_populated_mutex;
    pthread_cond_t*  vocab_populated_cond;
};

struct CountVocabData
{
    pthread_mutex_t* vocab_populated_mutex;
    pthread_cond_t*  vocab_populated_cond;
    std::queue<std::string>* line_queue;
};

struct ThreadData
{
    ThreadFunction threadFunction;
    void* threadArgs;
};

namespace ParentThread
{
    pthread_t* spawnWorkerThreads(ThreadData* threadData[], const int numThreads)
    {
        pthread_t* threads[numThreads];
        for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
        {
            threads[i] = Threading::spawnThread((*threadData)[i].threadFunction, (*threadData)[i].threadArgs);
        }
        return *threads;
    }
    Success monitorAndUpdateProgressBar(ProgressBar& progressBar);
}
