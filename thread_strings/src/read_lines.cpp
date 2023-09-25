/* 
 * @brief Child thread to populate queue from testfile.txt
 *
 * Important to use safeAction for mutex unlocking/locking as the queue will be touched by countvocabstrings as well
 * Will use lines_read_cond to communicate to other threads that its work is done
 */


#include "read_lines.hpp"
#include "parent_thread.hpp"
#include "input_handling.hpp"

void* ReadLines::readlines(void* args)
{
    ReadLinesData* readLinesData = (ReadLinesData*)args;
    FileHandler::forEachLineOfFile(readLinesData->testfile_path, [&](const std::string& line){
        Threading::safeAction(readLinesData->line_queue_data->line_queue_mutex, [&](){
            readLinesData->line_queue_data->line_queue->push(line);
        });
    });
    *readLinesData->line_queue_data->lines_read_cond = true;
    return NULL;
}