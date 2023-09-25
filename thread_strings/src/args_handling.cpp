/* 
 * @brief Class Handles Command line argument parsing and validation
 *
 * Args object made of optional and mandatory args structs
 * Struct will lay out default values for flags if none are passed in
 * Getopt will be used to parse optional arguments if given
 * Appropriate error messages will be displayed for incorrect usages
 * Program mandates two arguments for the file inputs
 * See macros for more usage details
 * 
 */

#include "args_handling.hpp"
#include <getopt.h>
#include <unistd.h>
#include <iostream>

#define VOCAB_FILE_INDEX 1
#define TEST_FILE_INDEX 2
#define INIT_LOOP_COUNTER 0

#define NUM_MANDATORY_ARGS 2
#define INVALID -1
#define FLAG_OPTIONS "p:m:v:"
#define P_FLAG_IDENTIFER 'p'
#define M_FLAG_IDENTIFER 'm'
#define V_FLAG_IDENTIFER 'v'
#define OUT_OF_RANGE_P_FLAG(p_flag) p_flag<10
#define OUT_OF_RANGE_M_FLAG(m_flag) m_flag<=0 || m_flag>SPECIAL_MARK_INTERVAL_M_FLAG_DEFAULT
#define INVALID_P_FLAG_ERROR_MESSAGE "Number of progress marks must be a number and at least 10"
#define INVALID_M_FLAG_ERROR_MESSAGE "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10"
#define DEFAULT_ERROR_MESSAGE "Usage: %s vocab.txt testFile.txt -p progress_marks -m mark_characters -v num_vocab_strings"

namespace
{
    void validate_pFlag(const OptionalArgs& optionalArgs)
    {
        if (OUT_OF_RANGE_P_FLAG(optionalArgs.p_flag)) {
            printf(INVALID_P_FLAG_ERROR_MESSAGE);
            exit(EXIT_FAILURE);
        }
    }

    void validate_mFlag(const OptionalArgs& optionalArgs)
    {
        if (OUT_OF_RANGE_M_FLAG(optionalArgs.m_flag)) {
            printf(INVALID_M_FLAG_ERROR_MESSAGE);
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
        if (argc - optind < NUM_MANDATORY_ARGS) printDefaultError(argv);
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
                    validate_pFlag(optionalArgs);
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

const char* ArgsHandling::getVocabPath(char* argv[])
{
    return argv[VOCAB_FILE_INDEX];
}

const char* ArgsHandling::getTestFilePath(char* argv[])
{
    return argv[TEST_FILE_INDEX];
}

std::ostream& operator<<(std::ostream& stream, Args& args)
{
    return stream << args.mandatoryArgs.sourceVocab << args.mandatoryArgs.testFile << args.optionalArgs.m_flag << args.optionalArgs.p_flag << args.optionalArgs.v_flag;
}