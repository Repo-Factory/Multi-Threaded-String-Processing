/* 
 * @brief FileHandler namespace defines functions for file operations
 *
 * This is used for interacting with vocabulary.txt and testfile.txt files that get passed in.
 */


#include "input_handling.hpp"
#include <fstream>
#include <string>
#include <vector>

#define FILE_OPEN_ERROR_MESSAGE "Failed to open the file %s"
#define COUNT_NEW_LINE 1

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
            progressTracker+=word.size()+COUNT_NEW_LINE;
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

/* Count number of lines in file */
int FileHandler::getLineCount(const std::string& filename)
{
    std::ifstream stream = openFile(filename);
    std::string line;
    int lineCount=0;
    while (std::getline(stream, line))
        lineCount++;    
    stream.close();
    return lineCount;
}

/* Count number of characters in file */
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