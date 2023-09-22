#pragma once
#include <vector>
#include <string>

namespace ReadVocab
{
    void* readvocab(void* vocabFile);
    std::vector<std::string>& readVocabIntoStorage(std::vector<std::string>& vocab, char* vocabFile);
}
