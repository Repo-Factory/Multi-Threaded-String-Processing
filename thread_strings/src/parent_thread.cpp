#include "parent_thread.hpp"
#include "progress_bar.hpp"
#include "input_handling.hpp"
#include <array>
#include <memory>
#include <unordered_map>

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

namespace
{
    void displayTotalFileMetric(const int fileMetricCount, const char* filename, const std::string& metric)
    {
        printf("There are %d %s in %s\n", fileMetricCount, metric.c_str(), filename);
    }

    int monitorAndUpdateProgressBar(const int p_flag, const int m_flag, const int metricTotal, int& metricProgress)
    {
        const auto progressBar = std::unique_ptr<ProgressBar>(new ProgressBar(p_flag, m_flag, metricTotal));
        return progressBar->displayProgressBar(metricProgress);
    }
}

void ParentThread::monitorReadVocabBar(const Args& args, int& progressTracker)
{
    const int totalVocab = monitorAndUpdateProgressBar(
        args.optionalArgs.p_flag, args.optionalArgs.m_flag, FileHandler::getLetterCount(args.mandatoryArgs.sourceVocab), progressTracker
    );
    displayTotalFileMetric(totalVocab, args.mandatoryArgs.sourceVocab, COUNT_BY_CHARACTERS);
}

void ParentThread::monitorReadLinesBar(const Args& args, int& progressTracker)
{
    const int totalLinesProcessed = monitorAndUpdateProgressBar(
        args.optionalArgs.p_flag, args.optionalArgs.m_flag, FileHandler::getLineCount(args.mandatoryArgs.testFile), progressTracker
    );
    displayTotalFileMetric(totalLinesProcessed, args.mandatoryArgs.testFile, COUNT_BY_WORDS);
}