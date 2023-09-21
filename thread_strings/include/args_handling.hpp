#pragma once
#include <string>
#include <fstream>

#define PROGRESS_MARKS_P_FLAG_DEFAULT 50
#define PROGRESS_MARKS_P_FLAG_MINIMUM 10
#define CHARACTERS_FOR_MARK_M_FLAG_DEFAULT 10
#define OUT_OF_RANGE_M_FLAG(number) number<=0 || number>CHARACTERS_FOR_MARK_M_FLAG_DEFAULT
#define PRINT_VOCAB_STRINGS_V_FLAG_DEFAULT 0

struct MandatoryArgs
{
    char* sourceVocab;
    char* testFile;
};

struct OptionalArgs
{
    int p_flag = PROGRESS_MARKS_P_FLAG_DEFAULT;
    int m_flag = CHARACTERS_FOR_MARK_M_FLAG_DEFAULT;
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
    const std::string getVocabPath(char* argv[]);
    const std::string getTestFilePath(char* argv[]);
}

std::ostream& operator<<(std::ostream& stream, Args args);