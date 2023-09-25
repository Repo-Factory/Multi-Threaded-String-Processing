/* 
 * @brief Class Child thread to read vocab from vocabulary.txt into data structure
 *
 * Will use vocab_populated_cond to signal to countvocabstrings that its execution
 * has finished. getWordsArrayFromFile will keep track of progress for the progress bar
 * Progress will be determined by number of chars read in compared to total chars in the file
 */

#include "read_vocab.hpp"
#include "input_handling.hpp"
#include "parent_thread.hpp"

void* ReadVocab::readvocab(void* args)
{
    ReadVocabData* readVocabData = (ReadVocabData*)args;
    std::vector<std::string>* wordsStorage = FileHandler::getWordsArrayFromFile(
        std::string(readVocabData->vocab_path), readVocabData->vocab, *readVocabData->readInChars
    );
    *readVocabData->vocab_populated_cond = true;
    return NULL;
}
