#pragma once

#define PROGRESS_SYMBOL_DEFAULT "-"
#define PROGRESS_SYMBOL_SPECIAL "#"


class ProgressBar
{
    public:
        ProgressBar();
};
ProgressBar::ProgressBar() {}

float calculatePercentageTasksComplete(int tasksComplete, int totalTasks);
char determineSpecialOrDefault(int specialInterval, int currentIndex);
