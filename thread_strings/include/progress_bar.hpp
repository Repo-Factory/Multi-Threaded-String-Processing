#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <memory>

#define INIT_INT 0

class ProgressBar
{
    public:
        ProgressBar(const int p_flag_value, const int m_flag_value, const int metricTotal);
        static std::unique_ptr<ProgressBar> createProgressBar(const int totalMarks, const int specialInterval, const int metricTotal);
        char nextProgressBarChar(const int currentMetric, int currentProgress);
        int displayProgressBar(int& processedLines, int printedSymbols=INIT_INT);

    private:
        const int total_progress_marks; // p_flag
        const int special_mark_interval; // m_flag
        const int metricTotal;
};

#endif