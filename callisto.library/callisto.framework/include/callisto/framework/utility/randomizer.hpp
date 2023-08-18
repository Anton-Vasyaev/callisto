#pragma once

// std
#include <random>

namespace callisto::framework
{

/// @brief Presents random generation.
class randomizer
{
    std::mt19937 _engine;

    std::uniform_real_distribution<> _dist;

public:
    /// @brief Constructs randomizer.
    /// @param seed Seed of random generation.
    randomizer(int seed = 1024)
    {
        _engine = std::mt19937(seed);
        _dist   = std::uniform_real_distribution(0.0, 1.0);
    }

    /// @brief Returns random uniform value from 0.0 to 1.0
    /// @return Random value.
    inline double next() { return _dist(_engine); }

    /// @brief Returns random uniform value from min to max.
    /// @param min Min value.
    /// @param max Max value.
    /// @return Random value.
    inline double next_range(double min, double max)
    {
        auto next_val = next();

        return min + next_val * (max - min);
    }

    /// @brief Returns random bool value detemines by probability
    /// @param probability Probability of true value returning.
    /// @return Random bool value.
    inline bool next_bool(double probability = 0.5)
    {
        auto next_val = next();
        return next_val < probability ? true : false;
    }
};

} // namespace callisto::framework