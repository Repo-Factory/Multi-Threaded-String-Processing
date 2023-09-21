#pragma once
#include <vector>
#include <string>

struct VocabStorage
{
    std::vector<std::string> vocab;
};

namespace ReadVocab
{
    void* readvocab(void* vocabFile);
    VocabStorage* readVocabIntoStorage(char* vocabFile);
}
