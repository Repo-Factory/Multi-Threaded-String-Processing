/* 
 * @brief Child Thread to count substrings
 * 
 * Waits for vocab strings to be populated in read_vocab thread
 * Proceeds to take elements out of line_queue_data->line_queue as they come in from read_lines thread
 * and print out the number of counted substrings to output file
 * 
 * @dependency Trie
 */

#include "count_vocab_strings.hpp"
#include "threading.hpp"
#include "parent_thread.hpp"
#include "trie.hpp"
#include <iostream>
#include <memory>

#define NULL_TERMINATOR_CHAR '\0'
#define COUNTER_INIT 0
#define INCREMENT(number) number+=1

namespace 
{
    Trie* insertSuffixes(const char* word, Trie* trie) // Used to insert word from testfile.txt into trie
    {
        while (*word != NULL_TERMINATOR_CHAR)
        {
            trie->insertString(word++, trie->getRoot());   
        }
        return trie;
    } // Example: If we want to search great, we should insert great, reat, eat, at, and t for fast lookup of substrings

    int countSubstrings(const std::vector<std::string>& words, Trie* trie) // For each substring of vocab, increment count if found in trie
    {
        int substringCount = COUNTER_INIT;
        for (const std::string& line : words)
        {
            substringCount += trie->searchString(line.c_str(), trie->getRoot());
        }
        return substringCount;
    }

    const int getSubstringCount(const std::string& line, const std::vector<std::string>& words) // Called from main for every word in testfile
    {
        Trie* trie = new Trie();
        const int substringCount = countSubstrings(words, insertSuffixes(line.c_str(), trie));
        delete trie;
        return substringCount;
    }

    std::ostream& printSubstringCount(std::ostream& outputFile, const int v_flag_value, const int substringCount)
    {
        return substringCount > v_flag_value ? 
        outputFile << substringCount << std::endl : 
        outputFile;
    } // Only print if count is greater than v flag arg
}

namespace
{
    // Take first element of queue and print number of substrings. Then take it out of the queue and report more line progress (to main thread)
    void printSubstringCountOfQueueItem(const CountVocabData* countVocabData)
    {
        const int substringCount = getSubstringCount(countVocabData->line_queue_data->line_queue->front(), *countVocabData->vocab_data->vocab);
        printSubstringCount(countVocabData->output_data->output_file, countVocabData->output_data->v_flag_value, substringCount);
        countVocabData->line_queue_data->line_queue->pop();
        INCREMENT(*countVocabData->processed_lines_progress);
    }
}

// Wait for read_vocab thread before executing. Then we will count substrings of items in the line queue populated from read_lines thread
void* CountVocabStrings::countvocabstrings(void* args)
{
    CountVocabData* countVocabData = (CountVocabData*)args;
    Threading::waitForCondition(countVocabData->vocab_data->vocab_populated_cond); 
    while (!countVocabData->line_queue_data->line_queue->empty()) { 
        Threading::safeAction(countVocabData->line_queue_data->line_queue_mutex, [&](){
            printSubstringCountOfQueueItem(countVocabData);
        });
    }
    return NULL;
}
