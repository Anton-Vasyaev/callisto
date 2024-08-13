#pragma once

// std
#include <random>
// project
#include <callisto/math/primitives/range.hpp>

namespace callisto::utility
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
    /// @param min Min possible random value.
    /// @param max Max possible random value.
    /// @return Random value.
    inline double next_range(double min, double max)
    {
        auto next_val = next();

        return min + next_val * (max - min);
    }

    /// @brief Returns random uniform value in range.
    /// @tparam Type type of range.
    /// @param range Range of possible random value.
    /// @return Random value.
    template<typename type>
    inline double next_range(const callisto::math::range<type>& range)
    {
        return next_range(range.min, range.max);
    }

    /// @brief Returns random integer uniform value in range from min to max.
    /// @param min Minimal possible random value.
    /// @param max Maximum possible random value.
    /// @return Random integer value.
    inline int64_t next_int_range(int64_t min, int64_t max)
    {
        double min_d = min;
        double max_d = max + 1.0;

        auto rand_val = next_range(min, max);

        auto floor_val = (int64_t)std::floor(rand_val);
        if (floor_val == max + 1) floor_val -= 1;

        return floor_val;
    }

    /// @brief Returns random integer uniform value in range
    /// @param range Range of possible random value.
    /// @return Random integer value.
    inline int64_t next_int_range(const callisto::math::range_l& range)
    {
        return next_int_range(range.min, range.max);
    }

    /// @brief Returns random bool value detemines by probability
    /// @param probability Probability of true value returning.
    /// @return Random bool value.
    inline bool next_bool(double probability = 0.5)
    {
        auto next_val = next();
        return next_val < probability;
    }
};

} // namespace callisto::utility