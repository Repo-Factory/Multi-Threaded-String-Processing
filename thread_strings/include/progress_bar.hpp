#pragma once

#include <vector>
#include <string>
#include <queue>

#include <functional>
typedef const std::vector<std::string> WordVector;

class ProgressBar
{
    public:
        ProgressBar(int p_flag_value, int m_flag_value, int metricTotal);
        char nextProgressBarChar(const int currentMetric, std::string currentProgress);
        int displayReadVocabProgressBar(const WordVector& wordVector, std::string currentProgress="");
        int displayReadLineProgressBar(int& processedLines, std::string currentProgress="");

    private:
        const int total_progress_marks; // p_flag
        const int special_mark_interval; // n_flag
        const int metricTotal;
};
