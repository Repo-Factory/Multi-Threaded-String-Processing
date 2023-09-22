#include "parent_thread.hpp"
#include "progress_bar.hpp"
#include "read_lines.hpp"
#include "read_vocab.hpp"
#include "args_handling.hpp"
#include "count_vocab_strings.hpp"
#include "types.hpp"

#define NUM_CHILD_THREADS 3
#define THREAD_FAILED(thread_return_value) thread_return_value != 0 

int main(int argc, char * argv[])
{
    const Args args = ArgsHandling::processArgs(argc, argv);

    std::vector<std::string> vocab;
    pthread_mutex_t vocab_populated_mutex;
    std::atomic<bool>  vocab_populated_cond = ATOMIC_VAR_INIT(false);
    std::queue<std::string> line_queue;
    pthread_mutex_t line_queue_mutex;
    std::atomic<bool> lines_read_cond = ATOMIC_VAR_INIT(false);

    pthread_mutex_init(&line_queue_mutex, NULL);
    pthread_mutex_init(&vocab_populated_mutex, NULL);

    const ReadLinesData readLinesData   {ArgsHandling::getTestFilePath(argv), &line_queue_mutex, &lines_read_cond, &line_queue};
    const ReadVocabData readVocabData   {ArgsHandling::getVocabPath(argv), &vocab_populated_mutex, &vocab_populated_cond, &vocab};
    const CountVocabData countVocabData {&vocab_populated_mutex, &vocab_populated_cond, &line_queue_mutex, &lines_read_cond, &line_queue, &vocab};

    ThreadData readLinesThreadData  {&ReadLines::readlines, (void*)&readLinesData};
    ThreadData readVocabThreadData  {&ReadVocab::readvocab, (void*)&readVocabData};
    ThreadData countVocabThreadData {&CountVocabStrings::countvocabstrings, (void*)&countVocabData};
    const ThreadData* threadData[NUM_CHILD_THREADS] = {&readLinesThreadData, &readVocabThreadData, &countVocabThreadData};

    const std::array<pthread_t*, NUM_CHILD_THREADS> workerThreads = ParentThread::spawnWorkerThreads(threadData, NUM_CHILD_THREADS);
    for (int i = INIT_LOOP_COUNTER; i < NUM_CHILD_THREADS; i++)
    {
        if (THREAD_FAILED(pthread_join(*workerThreads[i], NULL))) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}