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
            trie->insertString(word, trie->getRoot());
            word++;
        }
        return trie;
    } // Example: If we want to search great, we should insert great, reat, eat, at, and t for fast lookup of substrings

    int countSubstrings(const std::vector<std::string>& words, Trie* trie) // For each substring of vocab, increment count if found in trie
    {
        int substringCount = COUNTER_INIT;
        for (std::string line : words)
        {
            if (trie->searchString(line.c_str(), trie->getRoot()))
                substringCount++;
        }
        return substringCount;
    }

    std::ostream& printSubstringCount(std::ostream& outputFile, const std::string line, const std::vector<std::string>& words) // Called from main for every word in testfile
    {
        Trie* trie = new Trie();
        std::cout << countSubstrings(words, insertSuffixes(line.c_str(), trie)) << std::endl;
        return outputFile;
    }
}

void* CountVocabStrings::countvocabstrings(void* args)
{
    CountVocabData* countVocabData = (CountVocabData*)args;
    std::ofstream outputFile(OUTPUT_FILE);
    /* wait for vocab thread */ sleep(1);
    /* try to pull something out of queue */
    while (1) { 
    if (!countVocabData->line_queue->empty()) {
        Threading::safeAction(countVocabData->line_queue_mutex, [&](){
            const std::string line = countVocabData->line_queue->front();
            printSubstringCount(outputFile, line, *countVocabData->vocab);
            countVocabData->line_queue->pop();
        });
    }
    }
    /* if something in queue, print substring count */
}
