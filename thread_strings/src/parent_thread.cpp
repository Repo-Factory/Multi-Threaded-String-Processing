#include "parent_thread.hpp"
#include "progress_bar.hpp"
#include <array>
#include <memory>
#include "input_handling.hpp"

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
    void displayTotalFileMetric(const int fileMetricCount, const char* filename)
    {
        printf("There are %d lines in %s\n", fileMetricCount, filename);
    }
}

Success ParentThread::monitorAndUpdateProgressBar(int p_flag, int m_flag, int metricTotal, int& processedLines)
{
    const auto vocabProgressBar =std::unique_ptr<ProgressBar>(new ProgressBar(
        p_flag, m_flag, metricTotal
    ));
    displayTotalFileMetric(vocabProgressBar->displayProgressBar(processedLines), "filename.c_str()");
    return Success{true};
}
