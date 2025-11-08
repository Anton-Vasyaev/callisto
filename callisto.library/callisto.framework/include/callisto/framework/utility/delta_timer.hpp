#pragma once

// std
#include <chrono>

namespace callisto::framework
{

class delta_timer
{
    using time_point_type = std::chrono::high_resolution_clock::time_point;

    time_point_type _prev_time;

    time_point_type _current_time;

public:
    void start()
    {
        _prev_time    = std::chrono::high_resolution_clock::now();
        _current_time = _prev_time;
    }

    void tick()
    {
        _prev_time = _current_time;

        _current_time = std::chrono::high_resolution_clock::now();
    }

    double delta()
    {
        namespace chr = std::chrono;

        auto ns_count = chr::duration_cast<chr::nanoseconds>(_current_time - _prev_time).count();

        auto seconds = static_cast<double>(ns_count) / 1'000'000'000.0;

        return seconds;
    }
};

} // namespace callisto::framework