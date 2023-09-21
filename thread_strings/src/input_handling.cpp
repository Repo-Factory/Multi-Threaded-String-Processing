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
    
    std::vector<std::string> storeWordsFromStream(std::ifstream stream) // Gets each line of file and stores it as string in vector
    {
        std::string word;
        std::vector<std::string> wordVector;
        while (std::getline(stream, word)) {
            wordVector.push_back(word);
        }
        stream.close();
        return wordVector;
    }
}

// Opens file and stores each line as new string in vector
// std::vector<std::string> FileHandler::getWordsArrayFromFile(const std::string& filename)
// {
//     return storeWordsFromStream(openFile(filename));
// }

// // Takes in function pointer param (well, C++ version) to perform passed in operation on each string of file passed in
// // I chose to do this to keep the function generic to file handling and keep file traversal logic out of main
// void FileHandler::forEachLineOfFile(const std::string& filename, const std::function<void(std::string&)> performOperation)
// {
//     std::ifstream stream = openFile(filename);
//     std::string line;
//     while (std::getline(stream, line)) {
//         performOperation(line);
//     }
//     stream.close();
// }