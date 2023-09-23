/* 
 * @brief FileHandler namespace defines functions for file operations
 *
 * This is used for interacting with vocabulary.txt and testfile.txt files that get passed in.
 */


#include "input_handling.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace
{
    #define FILE_OPEN_ERROR_MESSAGE "Failed to open the file %s"
}

namespace  
{
    std::ifstream openFile(const std::string& filename) // Generic open function.
    {
        std::ifstream stream(filename);
        if (stream.fail()) {
            printf(FILE_OPEN_ERROR_MESSAGE, filename.c_str());
            exit(EXIT_FAILURE);
        }
        return stream;
    } // Note the file will have to be closed at some point if this function is called
    
    std::vector<std::string>* storeWordsFromStream(std::ifstream stream, std::vector<std::string>* vocab, int& progressTracker) // Gets each line of file and stores it as string in vector
    {
        std::string word;
        while (std::getline(stream, word)) {
            vocab->push_back(word);
            progressTracker+=word.size()+1; // Account for newline
        }
        stream.close();
        return vocab;
    }
}

// Opens file and stores each line as new string in vector
std::vector<std::string>* FileHandler::getWordsArrayFromFile(const std::string& filename, std::vector<std::string>* vocab, int& progressTracker)
{
    return storeWordsFromStream(openFile(filename), vocab, progressTracker);
}

// Takes in function pointer param (well, C++ version) to perform passed in operation on each string of file passed in
// I chose to do this to keep the function generic to file handling and keep file traversal logic out of main
void FileHandler::forEachLineOfFile(const std::string& filename, const std::function<void(std::string&)> performOperation)
{
    std::ifstream stream = openFile(filename);
    std::string line;
    while (std::getline(stream, line)) {
        performOperation(line);
    }
    stream.close();
}

namespace
{
    const int recursiveLineCount(std::ifstream& stream, std::string& line, int currentLineCount=0)
    {
        return std::getline(stream, line) ? recursiveLineCount(stream, line, ++currentLineCount) : currentLineCount;
    }
}

int FileHandler::getLineCount(const std::string& filename)
{
    std::ifstream stream = openFile(filename);
    std::string line;
    const int lineCount = recursiveLineCount(stream, line);
    stream.close();
    return lineCount;
}

namespace
{
    const int recursiveCharCount(std::ifstream& stream, char& letter, int currentLetterCount=0)
    {
        return stream.get(letter) ? recursiveCharCount(stream, letter, ++currentLetterCount) : currentLetterCount;
    }
}

int FileHandler::getLetterCount(const std::string& filename)
{
    std::ifstream stream = openFile(filename);
    char letter;
    int letterCount=0;
    while (stream.get(letter))
        letterCount++;
    stream.close();
    return letterCount;
}