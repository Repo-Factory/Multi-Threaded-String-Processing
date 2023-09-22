#define NUM_OF_FILES 2
#define VOCAB_FILE_INDEX 0
#define TEST_FILE_INDEX 1
#define NUM_CHILD_THREADS 3


#include <queue>
#include <cstdarg>
#include <string>
#include <atomic>
#include <functional>
#include "sys/types.h"
#include "types.hpp"
#include "progress_bar.hpp"
#include "threading.hpp"

struct ReadLinesData
{   
    const char* testfile_path;
    pthread_mutex_t* line_queue_mutex;
    std::atomic<bool>* lines_read_cond;
    std::queue<std::string>* line_queue;
};

struct ReadVocabData
{
    const char* vocab_path;
    pthread_mutex_t* vocab_populated_mutex;
    std::atomic<bool>*  vocab_populated_cond;
    std::vector<std::string>* vocab;
};

struct CountVocabData
{
    pthread_mutex_t* vocab_populated_mutex;
    std::atomic<bool>*  vocab_populated_cond;
    pthread_mutex_t* line_queue_mutex;
    std::atomic<bool>* lines_read_cond;
    std::queue<std::string>* line_queue;
    std::vector<std::string>* vocab;
};

struct ThreadData
{
    ThreadFunction threadFunction;
    void* threadArgs;
};

namespace ParentThread
{
    std::array<pthread_t*, NUM_CHILD_THREADS> spawnWorkerThreads(const ThreadData* threadData[], const int numThreads);
    Success monitorAndUpdateProgressBar(ProgressBar& progressBar);
}
