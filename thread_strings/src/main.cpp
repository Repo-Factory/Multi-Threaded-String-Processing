#include "parent_thread.hpp"
#include "progress_bar.hpp"
#include "read_lines.hpp"
#include "read_vocab.hpp"
#include "args_handling.hpp"
#include "count_vocab_strings.hpp"
#include "pthread.h"
#include "types.hpp"
#include <iostream>

#define NUM_CHILD_THREADS 3

pthread_t* ParentThread::spawnWorkerThreads(const ThreadData* threadData[], const int numThreads)
{
    pthread_t* threads[numThreads]; 
    for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
    {
        threads[i] = new pthread_t;
        threads[i] = Threading::spawnThread(threadData[i]->threadFunction, threadData[i]->threadArgs);
    }
    return *threads;
}

int main(int argc, char * argv[])
{
    const Args args = ArgsHandling::processArgs(argc, argv);

    pthread_mutex_t line_queue_mutex;
    pthread_cond_t lines_read_cond;
    std::queue<std::string> line_queue;
    pthread_mutex_t vocab_populated_mutex;
    pthread_cond_t  vocab_populated_cond;

    const ReadLinesData readLinesData  {ArgsHandling::getTestFilePath(argv).c_str(), &line_queue_mutex, &lines_read_cond, &line_queue};
    const ReadVocabData readVocabData  {ArgsHandling::getVocabPath   (argv).c_str(), &vocab_populated_mutex, &vocab_populated_cond};
    const CountVocabData countVocabData{&vocab_populated_mutex, &vocab_populated_cond, &line_queue};

    ThreadData readLinesThreadData =  ThreadData{&ReadLines::readlines,                  (void*)&readLinesData};
    ThreadData readVocabThreadData =  ThreadData{&ReadVocab::readvocab,                  (void*)&readVocabData};
    ThreadData countVocabThreadData = ThreadData{&CountVocabStrings::countvocabstrings, (void*)&countVocabData};
    const ThreadData* threadData[NUM_CHILD_THREADS] = {&readLinesThreadData, &readVocabThreadData, &countVocabThreadData};

    const pthread_t* workerThreads = ParentThread::spawnWorkerThreads(threadData, NUM_CHILD_THREADS);
    for (int i = 0; i < NUM_CHILD_THREADS; i++)
    {
        pthread_join(*workerThreads++, NULL);
    }
    
    return EXIT_SUCCESS;
}



