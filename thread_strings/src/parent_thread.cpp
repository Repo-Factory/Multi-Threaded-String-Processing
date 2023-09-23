#include "parent_thread.hpp"
#include "progress_bar.hpp"
#include <array>

std::array<pthread_t*, NUM_CHILD_THREADS> ParentThread::spawnWorkerThreads(const ThreadData* threadData[], const int numThreads)
{
    std::array<pthread_t*, NUM_CHILD_THREADS> threads;
    for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
    {
        threads[i] = new pthread_t;
        threads[i] = Threading::spawnThread(threadData[i]->threadFunction, threadData[i]->threadArgs);
    }
    return threads;
}

namespace
{
    void displayVocabFileWordCount(const int wordCount)
    {
        printf("\n%d\n", wordCount);
    }

    void displayTestFileLineCount(const int lineCount)
    {
        printf("\n%d\n", lineCount);
    }
}

Success ParentThread::monitorAndUpdateProgressBar(pthread_mutex_t* mutex, const WordVector& wordVector, const int totalWords, const int p_flag_value, const int m_flag_value)
{
//    const int totalVocab = ProgressBar::displayReadVocabProgressBar(mutex, wordVector, totalWords, p_flag_value, m_flag_value);
//    displayVocabFileWordCount(totalVocab);
//    displayTestFileLineCount(displayCountVocabProgressBar());
   return Success{true};
}
