#include "count_vocab_strings.hpp"

namespace
{
    Success forEachLineOfLineQueue(std::function<std::ostream&>(const std::string& line));
    int countVocabStrings(const std::string& line);
    bool isGreater(int count);
    std::ostream& outputToFile(std::ofstream& outputFile);
}

void* CountVocabStrings::countvocabstrings(void* lineQueue)
{
    printf("Making more threads bitch");
}
