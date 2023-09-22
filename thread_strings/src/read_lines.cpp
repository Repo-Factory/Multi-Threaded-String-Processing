#include "read_lines.hpp"
#include <stdio.h>
#include "parent_thread.hpp"
#include "input_handling.hpp"
#include "args_handling.hpp"
#include <iostream>

void debugPrint(std::queue<std::string>* queue)
{
    const std::string word = queue->front();
    queue->pop();
    std::cout << word << std::endl;
}

void* ReadLines::readlines(void* args)
{
    ReadLinesData* readLinesData = (ReadLinesData*)args;
    FileHandler::forEachLineOfFile(readLinesData->testfile_path, [&](const std::string& line){
        Threading::safeAction(readLinesData->line_queue_mutex, [&](){
            readLinesData->line_queue->push(line);
            // debugPrint(readLinesData->line_queue);
        });
    });
    return NULL;
}

// debugPrint(readLinesData->line_queue);
