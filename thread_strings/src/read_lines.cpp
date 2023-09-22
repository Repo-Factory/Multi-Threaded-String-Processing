#include "read_lines.hpp"
#include <stdio.h>
#include "parent_thread.hpp"
#include "input_handling.hpp"
#include "args_handling.hpp"
#include <iostream>

void* ReadLines::readlines(void* args)
{
    ReadLinesData* readLinesData = (ReadLinesData*)args;
    FileHandler::forEachLineOfFile(readLinesData->testfile_path, [&](const std::string& line){
        Threading::safeAction(readLinesData->line_queue_mutex, [&](){
            readLinesData->line_queue->push(line);
        });
    });
    *readLinesData->lines_read_cond = true;
    return NULL;
}