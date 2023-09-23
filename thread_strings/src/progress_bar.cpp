#include "progress_bar.hpp"
#include "threading.hpp"
#include <unistd.h>
#include <iostream>

#define PROGRESS_SYMBOL_DEFAULT '-'
#define PROGRESS_SYMBOL_SPECIAL '#'
#define EMPTY_CHAR ""
#define IS_MODULO(index, modulo) index%modulo==0

namespace
{
    char determineSpecialOrDefault(const int specialInterval, const int currentIndex)
    {
        return IS_MODULO((currentIndex+1), specialInterval) ? PROGRESS_SYMBOL_SPECIAL : PROGRESS_SYMBOL_DEFAULT;
    }

    bool printProgressChar(const char c)
    {
        std::cout << c; std::cout.flush();
        return c;   // Will return false if empty char character passed in
    }
}

ProgressBar::ProgressBar(int total_progress_marks, int special_mark_interval, int metricTotal) :
    total_progress_marks{total_progress_marks}, 
    special_mark_interval{special_mark_interval}, 
    metricTotal{metricTotal} 
{}

char ProgressBar::nextProgressBarChar(const int currentMetric, int printedSymbols)
{
    const float percentComplete = (float)currentMetric / this->metricTotal;
    const int charsToDisplay =  percentComplete * this->total_progress_marks;
    return printedSymbols < charsToDisplay ? determineSpecialOrDefault(this->special_mark_interval, printedSymbols) : *EMPTY_CHAR;
}

int ProgressBar::displayProgressBar(int& metric, int printedSymbols)
{
    while (metric != this->metricTotal) {
        printedSymbols += printProgressChar(nextProgressBarChar(metric, printedSymbols));
    }
    std::cout << nextProgressBarChar(metric, printedSymbols) << std::endl;
    return metric;
}
