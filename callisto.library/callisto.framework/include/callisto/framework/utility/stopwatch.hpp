#pragma once

// std
#include <chrono>

namespace callisto::framework
{

/// @brief Implements the logic of the stopwatch.
class stopwatch
{
public:
    /// @brief Type of time point.
    using time_point = decltype(std::chrono::high_resolution_clock::now());

private:
    uint64_t _total_nanoseconds = 0;

    time_point _start;

public:
    /// @brief Starts the stopwatch.
    void start() { _start = std::chrono::high_resolution_clock::now(); }

    /// @brief Stops the stopwatch.
    void stop()
    {
        namespace _chr = std::chrono;

        auto end = _chr::high_resolution_clock::now();

        _total_nanoseconds += _chr::duration_cast<_chr::nanoseconds>(end - _start).count();
    }

    /// @brief Reset the stopwatch.
    void reset() { _total_nanoseconds = 0; }

    /// @brief Resets and starts the stopwatch.
    void restart()
    {
        reset();
        start();
    }

    /// @brief Returns the number of nanoseconds of the stopwatch.
    /// @return Number of nanoseconds.
    double nanoseconds() { return static_cast<double>(_total_nanoseconds); }

    /// @brief Returns the number of microseconds of the stopwatch.
    /// @return Number of microseconds.
    double microseconds() { return nanoseconds() / 1000; }

    /// @brief Returns the number of milliseconds of the stopwatch.
    /// @return Number of milliseconds.
    double milliseconds() { return microseconds() / 1000; }

    /// @brief Returns the number of seconds of the stopwatch.
    /// @return Number of seconds.
    double seconds() { return milliseconds() / 1000; }
};

} // namespace callisto::framework
