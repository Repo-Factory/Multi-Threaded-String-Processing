#include "count_vocab_strings.hpp"
#include "threading.hpp"
#include "parent_thread.hpp"
#include "trie.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <unistd.h>

#define NULL_TERMINATOR_CHAR '\0'
#define COUNTER_INIT 0
#define V_FLAG 0
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

    std::ostream& printSubstringCount(std::ostream& outputFile, const std::string line, const std::vector<std::string>& words) // Called from main for every word in testfile
    {
        Trie* trie = new Trie();
        const int substringCount = countSubstrings(words, insertSuffixes(line.c_str(), trie));
        delete trie;
        return substringCount > V_FLAG ? outputFile << substringCount << std::endl : outputFile;
    }
}

namespace
{
    void printSubstringCountOfQueueItem(const std::string& line, const CountVocabData* countVocabData, std::ofstream& outputFile)
    {
        printSubstringCount(outputFile, line, *countVocabData->vocab);
        countVocabData->line_queue->pop();
        INCREMENT(*countVocabData->processedLines);
    }
}

void* CountVocabStrings::countvocabstrings(void* args)
{
    CountVocabData* countVocabData = (CountVocabData*)args;
    Threading::waitForCondition(countVocabData->vocab_populated_cond); 
    while (!countVocabData->line_queue->empty()) { 
        Threading::safeAction(countVocabData->line_queue_mutex, [&](){
            printSubstringCountOfQueueItem(countVocabData->line_queue->front(), countVocabData, countVocabData->output_file);
        });
    }
    return NULL;
}
