#ifndef ARGS_HANDLING_H
#define ARGS_HANDLING_H

#include <string>
#include <fstream>

#define PROGRESS_MARKS_P_FLAG_DEFAULT 50
#define PROGRESS_MARKS_P_FLAG_MINIMUM 10
#define SPECIAL_MARK_INTERVAL_M_FLAG_DEFAULT 10
#define PRINT_VOCAB_STRINGS_V_FLAG_DEFAULT 0

struct MandatoryArgs
{
    char* sourceVocab;
    char* testFile;
};

struct OptionalArgs
{
    int p_flag = PROGRESS_MARKS_P_FLAG_DEFAULT;
    int m_flag = SPECIAL_MARK_INTERVAL_M_FLAG_DEFAULT;
    int v_flag = PRINT_VOCAB_STRINGS_V_FLAG_DEFAULT;
};

struct Args
{   
    MandatoryArgs mandatoryArgs;
    OptionalArgs optionalArgs;
};

namespace ArgsHandling
{
    Args processArgs(int argc, char* argv[]);
    const char* getVocabPath(char* argv[]);
    const char* getTestFilePath(char* argv[]);
}

std::ostream& operator<<(std::ostream& stream, Args& args);

#endif