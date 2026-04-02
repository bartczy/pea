//
// Created by bartek on 12.03.2026.
//

#ifndef LAB01_TIMER_H
#define LAB01_TIMER_H
#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    double stop() {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }
};
#endif //LAB01_TIMER_H