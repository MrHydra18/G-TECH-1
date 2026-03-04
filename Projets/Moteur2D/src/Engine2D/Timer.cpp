#include "Timer.h"

Timer::Timer() : sink(0)
{
}

void Timer::Start()
{
    start_time = std::chrono::steady_clock::now();
}

void Timer::End()
{
    end_time = std::chrono::steady_clock::now();
}

int Timer::Diff()
{
    // Retourne le temps en millisecondes
    const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return static_cast<int>(diff.count());
}
