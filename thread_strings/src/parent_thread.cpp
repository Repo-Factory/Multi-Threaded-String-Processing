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
#define PROGRESS_COMPLETE_MESSAGE "There are %d %s in %s\n"

typedef std::array<pthread_t*, NUM_CHILD_THREADS> ThreadArray;

ThreadArray ParentThread::spawnWorkerThreads(const ThreadData* threadData[], const int numThreads)
{
    ThreadArray threads;
    for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
    {
        threads[i] = new pthread_t;
        threads[i] = Threading::spawnThread(threadData[i]->threadFunction, threadData[i]->threadArgs);
    }
    return threads;
}

int ParentThread::cleanWorkerThreads(const ThreadArray threads, const int numThreads)
{
    for (int i = INIT_LOOP_COUNTER; i < numThreads; i++)
    {
        delete(threads[i]);
    }
    return EXIT_SUCCESS;
}

void ParentThread::monitorReadVocabBar(const Args& args, int& progressTracker)
{
    const auto progressBar = ProgressBar::createProgressBar(args.optionalArgs.p_flag, args.optionalArgs.m_flag, FileHandler::getLetterCount(args.mandatoryArgs.sourceVocab));
    const int totalVocab = progressBar->displayProgressBar(progressTracker);
    printf(PROGRESS_COMPLETE_MESSAGE, FileHandler::getLineCount(args.mandatoryArgs.sourceVocab), args.mandatoryArgs.sourceVocab, COUNT_BY_WORDS);
}

void ParentThread::monitorReadLinesBar(const Args& args, int& progressTracker)
{
    const auto progressBar = ProgressBar::createProgressBar(args.optionalArgs.p_flag, args.optionalArgs.m_flag, FileHandler::getLineCount(args.mandatoryArgs.testFile));
    const int totalLinesProcessed = progressBar->displayProgressBar(progressTracker);
    printf(PROGRESS_COMPLETE_MESSAGE, totalLinesProcessed, args.mandatoryArgs.testFile, COUNT_BY_WORDS);
}