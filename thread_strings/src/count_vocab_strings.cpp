#include "count_vocab_strings.hpp"
#include "threading.hpp"
#include "parent_thread.hpp"
#include "trie.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <unistd.h>

#define OUTPUT_FILE "countNumOfContainedVocab.txt"
#define NULL_TERMINATOR_CHAR '\0'
#define COUNTER_INIT 0

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
        for (const std::string line : words)
        {
            substringCount += trie->searchString(line.c_str(), trie->getRoot());
        }
        return substringCount;
    }

    std::ostream& printSubstringCount(std::ostream& outputFile, const std::string line, const std::vector<std::string>& words) // Called from main for every word in testfile
    {
        Trie* trie = new Trie();
        const int substringCount = countSubstrings(words, insertSuffixes(line.c_str(), trie));
        if (substringCount != 0) std::cout <<  substringCount << std::endl;
        return outputFile << substringCount;
    }
}

namespace
{
    void printItemOfQueue(const std::string& line, CountVocabData* countVocabData, std::ofstream& outputFile)
    {
        printSubstringCount(outputFile, line, *countVocabData->vocab);
        countVocabData->line_queue->pop();
    }
}

void* CountVocabStrings::countvocabstrings(void* args)
{
    CountVocabData* countVocabData = (CountVocabData*)args;
    std::ofstream outputFile(OUTPUT_FILE);
    Threading::waitForCondition(countVocabData->vocab_populated_cond); 
    while (!countVocabData->line_queue->empty()) { 
        Threading::safeAction(countVocabData->line_queue_mutex, [&](){
            printItemOfQueue(countVocabData->line_queue->front(), countVocabData, outputFile);
        });
    }
    return NULL;
}
