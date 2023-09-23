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
        char nextProgressBarChar(const int currentMetric, int currentProgress);
        int displayProgressBar(int& processedLines, int currentProgress=0);

    private:
        const int total_progress_marks; // p_flag
        const int special_mark_interval; // n_flag
        const int metricTotal;
};
