/* 
 * @brief Class to abstract a progress bar
 *
 * A progress bar is an object that will measure progress based off some kind of metric
 * It will use the current value of the metric and the total possible value 
 * to calculate the percentage it has progressed. Then using this data, it 
 * can compare to how many marks it has already printed and then decide to
 * print more marks if needed.
 */

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
        std::cout << c; 
        std::cout.flush();
        return c;   // Will return false if empty char character passed in
    }
}

ProgressBar::ProgressBar(const int total_progress_marks, const int special_mark_interval, const int metricTotal) :
    total_progress_marks{total_progress_marks}, 
    special_mark_interval{special_mark_interval}, 
    metricTotal{metricTotal} 
{}  // Constructor will simply init const int members. These will determine the progress bar's behavior

// Will determine if next char needs to be printed based on current marks and theoretical desired marks based on metric progress
char ProgressBar::nextProgressBarChar(const int currentMetricProgress, const int printedSymbols)
{
    const float percentComplete = (float)currentMetricProgress / this->metricTotal;
    const int charsToDisplay =  percentComplete * this->total_progress_marks;
    return printedSymbols < charsToDisplay ? determineSpecialOrDefault(this->special_mark_interval, printedSymbols) : *EMPTY_CHAR;
}

// Will constantly call nextProgressBarChar to always be printing a new symbol if needed
int ProgressBar::displayProgressBar(int& metric, int printedSymbols)
{
    while (metric != this->metricTotal) {
        printedSymbols += printProgressChar(nextProgressBarChar(metric, printedSymbols)); // will increment printedSymbols if nextProgressBarChar returns true
    }
    std::cout << nextProgressBarChar(metric, printedSymbols) << std::endl;
    return metric;
}
