#include "read_vocab.hpp"
#include "input_handling.hpp"
#include "parent_thread.hpp"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

void* ReadVocab::readvocab(void* args)
{
    ReadVocabData* readVocabData = (ReadVocabData*)args;
    std::vector<std::string>* wordsStorage = FileHandler::getWordsArrayFromFile(
        std::string(readVocabData->vocab_path), readVocabData->vocab
    );
    *readVocabData->vocab_populated_cond = true;
    return NULL;
}
