/* 
 * @brief Class Parent thread will spawn children and monitor progress
 *
 * General function written to spawn any number of threads given the ThreadData which has the function with args to run
 * After spawning the threads, the parent thread's job is to create and monitor the progress bars
 * First it will monitor the readvocab thread, then the countsubstring thread
 */

#include "parent_thread.hpp"
#include "progress_bar.hpp"
#include "input_handling.hpp"
#include <array>
#include <memory>

#define INIT_LOOP_COUNTER 0
#define COUNT_BY_CHARACTERS "characters"
#define COUNT_BY_WORDS "lines"

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

int ParentThread::cleanWorkerThreads(std::array<pthread_t*, NUM_CHILD_THREADS> threads, const int numThreads)
{
    for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
    {
        delete(threads[i]);
    }
    return EXIT_SUCCESS;
}

namespace
{
    std::unique_ptr<ProgressBar> createProgressBar(const int totalMarks, const int specialInterval, const int metricTotal)
    {
        return std::unique_ptr<ProgressBar>(new ProgressBar(totalMarks, specialInterval, metricTotal));
    }

    int monitorAndUpdateProgressBar(const std::unique_ptr<ProgressBar>& progressBar, int& metricProgress)
    {
        return progressBar->displayProgressBar(metricProgress);
    }

    void displayTotalFileMetric(const int fileMetricCount, const char* filename, const std::string& metric_type)
    {
        printf("There are %d %s in %s\n", fileMetricCount, metric_type.c_str(), filename);
    }
}

void ParentThread::monitorReadVocabBar(const Args& args, int& progressTracker)
{
    const auto progressBar = createProgressBar(args.optionalArgs.p_flag, args.optionalArgs.m_flag, FileHandler::getLetterCount(args.mandatoryArgs.sourceVocab));
    const int totalVocab = monitorAndUpdateProgressBar(progressBar, progressTracker);
    displayTotalFileMetric(FileHandler::getLineCount(args.mandatoryArgs.sourceVocab), args.mandatoryArgs.sourceVocab, COUNT_BY_WORDS);
}

void ParentThread::monitorReadLinesBar(const Args& args, int& progressTracker)
{
    const auto progressBar = createProgressBar(args.optionalArgs.p_flag, args.optionalArgs.m_flag, FileHandler::getLineCount(args.mandatoryArgs.testFile));
    const int totalLinesProcessed = monitorAndUpdateProgressBar(progressBar, progressTracker);
    displayTotalFileMetric(totalLinesProcessed, args.mandatoryArgs.testFile, COUNT_BY_WORDS);
}