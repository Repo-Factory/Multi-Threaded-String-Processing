#pragma once
#include <vector>

struct VocabStorage
{
    std::vector<std::string> vocab;
};

namespace ReadVocab
{
    void* readvocab(void* vocabFile);
    VocabStorage* readVocabIntoStorage(char* vocabFile);
}
