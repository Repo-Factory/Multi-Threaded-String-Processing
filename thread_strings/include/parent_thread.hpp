#ifndef PARENT_THREAD_H
#define PARENT_THREAD_H

#define NUM_CHILD_THREADS 3

#include <queue>
#include <cstdarg>
#include <string>
#include <atomic>
#include <fstream>
#include <functional>
#include "sys/types.h"
#include "progress_bar.hpp"
#include "threading.hpp"
#include "args_handling.hpp"

struct LineQueueData
{
    std::queue<std::string>* line_queue;
    pthread_mutex_t* line_queue_mutex;
    std::atomic<bool>* lines_read_cond;
};

struct VocabData
{
    std::vector<std::string>* vocab;
    pthread_mutex_t* vocab_populated_mutex;
    std::atomic<bool>*  vocab_populated_cond;
};

struct OutputData
{
    int v_flag_value;
    std::ofstream& output_file;
};

struct ReadLinesData
{   
    const char* testfile_path;
    LineQueueData* line_queue_data;
};

struct ReadVocabData
{
    const char* vocab_path;
    VocabData* vocab_data;
    int* read_in_chars_progress;
};

struct CountVocabData
{
    VocabData* vocab_data;
    LineQueueData* line_queue_data;
    OutputData* output_data;
    int* processed_lines_progress;
};

struct ThreadData
{
    ThreadFunction threadFunction;
    void* threadArgs;
};

namespace ParentThread
{
    std::array<pthread_t*, NUM_CHILD_THREADS> spawnWorkerThreads(const ThreadData* threadData[], const int numThreads);
    int cleanWorkerThreads(const std::array<pthread_t*, NUM_CHILD_THREADS> threads, const int numThreads);
    void monitorReadVocabBar(const Args& args, int& progressTracker);
    void monitorReadLinesBar(const Args& args, int& progressTracker);
}

#endif