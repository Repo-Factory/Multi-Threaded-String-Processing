/*******************************************************************************
 * @author Conner Sommerfield
 * @author Dustin Cook
 * @name countvocabstrings
 * 
 * @details Reads words from two files passed as cmd line arguments 
 * For each line in file2, it will output to stdout the numbers of substrings
 * from file1 that are found. So the output will be an integer for each word in file2 on a new line.
 * 
 * This is done with thread child threads - a readVocab thread, a readLines thread, and a countSubstring thread
 * 
 * Program must be called like this or will gracefully exit: ./countvocabstrings vocab.txt testFile.txt -p progress_marks -m mark_characters -v num_vocab_strings
 * 
 * Relevant entities
 * - Dependencies
 *      - ProgressBar
 *      - Threading     - Generic threading functions
 *      - Trie   
 *          - CharsMap       
 * - ArgsHandling       - For command line arguments
 * - InputHandling      - For file operations
 * - ParentThread
 * - ChildThreads
 *      - readLines
 *      - readVocab
 *      - CountSubstrings
 * 
 * See cpp file of each for more details in each respective area
 * 
 ******************************************************************************/

#include "parent_thread.hpp"
#include "args_handling.hpp"

#include "read_lines.hpp"
#include "read_vocab.hpp"
#include "count_vocab_strings.hpp"

#define NUM_CHILD_THREADS 3
#define OUTPUT_FILE "countNumOfContainedVocab.txt"
typedef std::array<pthread_t*, NUM_CHILD_THREADS> ThreadArray;

int main(int argc, char* argv[])
{
    const Args args = ArgsHandling::processArgs(argc, argv);    // Handle input
    std::ofstream output_file = std::ofstream(OUTPUT_FILE);     // Handle output
    OutputData outputData {args.optionalArgs.v_flag, output_file};

    /* ***** INIT SHARED DATA **** */
    std::vector<std::string> vocab;
    pthread_mutex_t vocab_populated_mutex;
    std::atomic<bool>  vocab_populated_cond =  ATOMIC_VAR_INIT(false);
    pthread_mutex_init(&vocab_populated_mutex, NULL);
    VocabData vocabData {&vocab, &vocab_populated_mutex, &vocab_populated_cond};

    std::queue<std::string> line_queue;
    pthread_mutex_t line_queue_mutex;
    std::atomic<bool> lines_read_cond =        ATOMIC_VAR_INIT(false);
    pthread_mutex_init(&line_queue_mutex, NULL);
    LineQueueData lineQueueData {&line_queue, &line_queue_mutex, &lines_read_cond};

    int testFileProcessedLinesProgress =        INIT_INT;
    int vocabFileReadInCharsProgress =          INIT_INT;
    
    /* ***** DIRECT NEEDED SHARED DATA TO EACH THREAD **** */
    const ReadLinesData readLinesData   {args.mandatoryArgs.testFile, &lineQueueData};
    const ReadVocabData readVocabData   {args.mandatoryArgs.sourceVocab, &vocabData, &vocabFileReadInCharsProgress};
    const CountVocabData countVocabData {&vocabData, &lineQueueData, &outputData, &testFileProcessedLinesProgress};

    /* ***** TIE FUNCTIONS TO EACH THREAD **** */
    const ThreadData readLinesThreadData  {&ReadLines::readlines,                 (void*)&readLinesData};
    const ThreadData readVocabThreadData  {&ReadVocab::readvocab,                 (void*)&readVocabData};
    const ThreadData countVocabThreadData {&CountVocabStrings::countvocabstrings, (void*)&countVocabData};
    const ThreadData* threadData[NUM_CHILD_THREADS] = {&readLinesThreadData, &readVocabThreadData, &countVocabThreadData};

    /* ***** EXECUTE/MONITOR THREADS **** */
    const ThreadArray childThreads =        ParentThread::spawnWorkerThreads(threadData, NUM_CHILD_THREADS);
    ParentThread::monitorReadVocabBar       (args, vocabFileReadInCharsProgress);
    Threading::waitForCondition             (&lines_read_cond);
    ParentThread::monitorReadLinesBar       (args, testFileProcessedLinesProgress);
    return ParentThread::cleanWorkerThreads (childThreads, NUM_CHILD_THREADS);    
}