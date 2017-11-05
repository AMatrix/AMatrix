#pragma once

#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point _start;

   public:
    using duration_type = long long;
    Timer() : _start(std::chrono::high_resolution_clock::now()) {}
    std::chrono::milliseconds elapsed() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - _start);
    }
    void reset() { _start = std::chrono::high_resolution_clock::now(); }
};
