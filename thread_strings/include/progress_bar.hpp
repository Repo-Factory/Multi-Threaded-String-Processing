#pragma once

#include <vector>
#include <string>
#include <queue>
#include <functional>
#include "types.hpp"

class ProgressBar
{
    public:
        ProgressBar(const int p_flag_value, const int m_flag_value, const int metricTotal);
        char nextProgressBarChar(const int currentMetric, int currentProgress);
        int displayProgressBar(int& processedLines, int printedSymbols=INIT_INT);

    private:
        const int total_progress_marks; // p_flag
        const int special_mark_interval; // m_flag
        const int metricTotal;
};
