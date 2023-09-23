#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <functional>

namespace FileHandler
{
    std::vector<std::string>* getWordsArrayFromFile(const std::string& filename, std::vector<std::string>* vocab, int& progressTracker);
    void forEachLineOfFile(const std::string& filename, const std::function<void(std::string&)> performOperation);
    int getLineCount(const std::string& filename);
    int getLetterCount(const std::string& filename);
}