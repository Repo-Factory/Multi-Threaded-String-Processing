#include "args_handling.hpp"
#include <getopt.h>
#include <unistd.h>
#include <iostream>
#include "types.hpp"

#define VOCAB_FILE_INDEX 1
#define TEST_FILE_INDEX 2

#define NUM_MANDATORY_ARGS 2
#define INVALID -1
#define FLAG_OPTIONS "p:m:v:"
#define P_FLAG_IDENTIFER 'p'
#define M_FLAG_IDENTIFER 'm'
#define V_FLAG_IDENTIFER 'v'
#define INVALID_M_FLAG_ERROR_MESSAGE "Invalid value for -m flag. It should be between 1 and %d"
#define DEFAULT_ERROR_MESSAGE "Usage: %s -p progress_marks -m mark_characters -v vocab_strings vocab.txt testFile.txt"

namespace
{
    void validate_mFlag(OptionalArgs& optionalArgs)
    {
        if (OUT_OF_RANGE_M_FLAG(optionalArgs.m_flag)) {
            printf(INVALID_M_FLAG_ERROR_MESSAGE, CHARACTERS_FOR_MARK_M_FLAG_DEFAULT);
            exit(EXIT_FAILURE);
        }
    }

    void printDefaultError(char* argv[])
    {
        printf(DEFAULT_ERROR_MESSAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
}

namespace
{
    MandatoryArgs getMandadtoryArgs(int argc, char* argv[])
    {
        if (argc - optind != NUM_MANDATORY_ARGS) printDefaultError(argv);
        return MandatoryArgs{argv[VOCAB_FILE_INDEX], argv[TEST_FILE_INDEX]};
    }

    OptionalArgs getOptionalArgs(int argc, char* argv[])
    {
        OptionalArgs optionalArgs;
        int option_index = INIT_LOOP_COUNTER;
        while ((option_index = getopt(argc, argv, FLAG_OPTIONS)) != INVALID) 
        {
            switch (option_index) 
            {
                case P_FLAG_IDENTIFER:
                    optionalArgs.p_flag = std::stoi(optarg);
                    break;
                case M_FLAG_IDENTIFER:
                    optionalArgs.m_flag = std::stoi(optarg);
                    validate_mFlag(optionalArgs);
                    break;
                case V_FLAG_IDENTIFER:
                    optionalArgs.v_flag = std::stoi(optarg);
                    break;
                default:
                    printDefaultError(argv);
            }
        }
        return optionalArgs;
    }
}

Args ArgsHandling::processArgs(int argc, char* argv[])
{
    return Args{getMandadtoryArgs(argc, argv), getOptionalArgs(argc, argv)};
}

const std::string ArgsHandling::getVocabPath(char* argv[])
{
    return argv[VOCAB_FILE_INDEX];
}

const std::string ArgsHandling::getTestFilePath(char* argv[])
{
    return argv[TEST_FILE_INDEX];
}

std::ostream& operator<<(std::ostream& stream, Args args)
{
    return stream << args.mandatoryArgs.sourceVocab << args.mandatoryArgs.testFile << args.optionalArgs.m_flag << args.optionalArgs.p_flag << args.optionalArgs.v_flag;
}