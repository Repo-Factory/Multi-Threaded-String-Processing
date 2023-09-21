#include "progress_bar.hpp"

namespace
{
    float calculatePercentageTasksComplete(int tasksComplete, int totalTasks);
    char determineSpecialOrDefault(int specialInterval, int currentIndex);
}

ProgressBar::ProgressBar() {}