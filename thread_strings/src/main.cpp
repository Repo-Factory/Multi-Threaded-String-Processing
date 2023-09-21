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

int main(int argc, char * argv[])
{
    Args args = ArgsHandling::processArgs(argc, argv);

    pthread_mutex_t line_queue_mutex;
    pthread_cond_t lines_read_cond;
    std::queue<std::string> line_queue;
    pthread_mutex_t vocab_populated_mutex;
    pthread_cond_t  vocab_populated_cond;

    ReadLinesData readLinesData{ArgsHandling::getTestFilePath(argv).c_str(), &line_queue_mutex, &lines_read_cond, &line_queue};
    ReadVocabData readVocabData{ArgsHandling::getVocabPath(argv).c_str(), &vocab_populated_mutex, &vocab_populated_cond};
    CountVocabData countVocabData{&vocab_populated_mutex, &vocab_populated_cond, &line_queue};

    ThreadData readLinesThreadData = ThreadData{&ReadLines::readlines,                  (void*)&readLinesData};
    ThreadData readVocabThreadData = ThreadData{&ReadVocab::readvocab,                  (void*)&readVocabData};
    ThreadData countVocabThreadData = ThreadData{&CountVocabStrings::countvocabstrings, (void*)&countVocabData};
    ThreadData* threadData[] = {&readLinesThreadData, &readVocabThreadData, &countVocabThreadData};

    pthread_t* workerThreads = ParentThread::spawnWorkerThreads(threadData, NUM_CHILD_THREADS);


    return EXIT_SUCCESS;
}



