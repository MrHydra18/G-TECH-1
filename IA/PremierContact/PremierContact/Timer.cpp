#include "Timer.h"
#include <thread>

float Timer::GetCurrentTime()
{
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    return (float)(ms.count());
}

float Timer::Start()
{
    m_start = GetCurrentTime();

    return m_start;
}

float Timer::End()
{
    m_end = GetCurrentTime();

    return m_end;
}

void Timer::Sleep(int _milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(_milliseconds));
}

void Timer::ResetTimer()
{
    m_start = 0;
    m_end = 0;
}