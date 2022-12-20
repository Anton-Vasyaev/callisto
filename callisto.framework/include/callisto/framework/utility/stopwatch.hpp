#pragma once

// std
#include <chrono>

namespace callisto::framework
{

namespace
{
namespace _chr = std::chrono;
}

/// @brief Implements the logic of the stopwatch.
class stopwatch
{
public:
    /// @brief Type of time point.
    using time_point = decltype(_chr::high_resolution_clock::now());

private:
    uint64_t _total_nanoseconds = 0;

    time_point _start;

public:
    /// @brief Starts the stopwatch.
    inline void start() { _start = _chr::high_resolution_clock::now(); }

    /// @brief Stops the stopwatch.
    inline void stop()
    {
        auto end = _chr::high_resolution_clock::now();

        _total_nanoseconds += _chr::duration_cast<_chr::nanoseconds>(end - _start).count();
    }

    /// @brief Reset the stopwatch.
    inline void reset() { _total_nanoseconds = 0; }

    /// @brief Resets and starts the stopwatch.
    inline void restart()
    {
        reset();
        start();
    }

    /// @brief Returns the number of nanoseconds of the stopwatch.
    /// @return Number of nanoseconds.
    inline double nanoseconds() { return _total_nanoseconds; }

    /// @brief Returns the number of microseconds of the stopwatch.
    /// @return Number of microseconds.
    inline double microseconds() { return nanoseconds() / 1000; }

    /// @brief Returns the number of milliseconds of the stopwatch.
    /// @return Number of milliseconds.
    inline double milliseconds() { return microseconds() / 1000; }

    /// @brief Returns the number of seconds of the stopwatch.
    /// @return Number of seconds.
    inline double seconds() { return milliseconds() / 1000; }
};

} // namespace callisto::framework
