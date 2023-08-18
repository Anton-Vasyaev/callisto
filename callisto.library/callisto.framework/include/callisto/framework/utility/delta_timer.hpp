#pragma once

// std
#include <chrono>

namespace callisto::framework
{

namespace
{
    namespace chr = std::chrono;
}


class delta_timer
{
    using time_point_type = chr::high_resolution_clock::time_point;

    time_point_type _prev_time;

    time_point_type _current_time;

public:
    inline void start()
    {
        _prev_time = chr::high_resolution_clock::now();
        _current_time = _prev_time;
    }

    inline void tick()
    {
        _prev_time = _current_time;

        _current_time = chr::high_resolution_clock::now();
    }

    inline double delta()
    {
        auto ns_count = chr::duration_cast<chr::nanoseconds>(_current_time - _prev_time).count();

        auto seconds = ns_count / 1'000'000'000.0;

        return seconds;
    }
};

}