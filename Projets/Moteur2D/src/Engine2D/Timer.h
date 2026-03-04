#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>

class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
    std::chrono::time_point<std::chrono::steady_clock> end_time;
    volatile int sink;

public:
    Timer();

    void Start();
    void End();
    int Diff();

};