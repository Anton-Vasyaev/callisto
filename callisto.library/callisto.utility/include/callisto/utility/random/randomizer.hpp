#pragma once

// std
#include <random>
// project
#include <callisto/math/primitives/range.hpp>
#include <callisto/framework/concepts.hpp>

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
    explicit randomizer(int seed = 1024)
    {
        _engine = std::mt19937(seed);
        _dist   = std::uniform_real_distribution(0.0, 1.0);
    }

    /// @brief Returns random uniform value from 0.0 to 1.0
    /// @tparam type floating point type of return value.
    /// @return Random value.
    template<callisto::framework::concept_floating_point type = double>
    type next()
    {
        return _dist(_engine);
    }

    /// @brief Returns random uniform value from min to max.
    /// @tparam type floating point type of arguments and return vale.
    /// @param min Min possible random value.
    /// @param max Max possible random value.
    /// @return Random value.
    template<callisto::framework::concept_floating_point type = double, typename arg_type = double>
    type next_range(arg_type min, arg_type max)
    {
        auto next_val = next();

        return min + next_val * (max - min);
    }

    /// @brief Returns random uniform value in range.
    /// @tparam type type of range.
    /// @param range Range of possible random value.
    /// @return Random value.
    template<callisto::framework::concept_floating_point type = double, typename arg_type = double>
    double next_range(const callisto::math::range<arg_type>& range)
    {
        return next_range(range.min, range.max);
    }

    /// @brief Returns random integer uniform value in range from min to max.
    /// @tparam int_type integer type of arguments and return value.
    /// @param min Minimal possible random value.
    /// @param max Maximum possible random value.
    /// @return Random integer value.
    template<callisto::framework::concept_integer int_type = int32_t>
    int_type next_int_range(int_type min, int_type max)
    {
        const double min_d = static_cast<double>(min);
        const double max_d = static_cast<double>(max) + 1.0;

        auto rand_val = next_range(min_d, max_d);

        auto floor_val = static_cast<int_type>(std::floor(rand_val));
        if (floor_val == max + 1) floor_val -= 1;

        return floor_val;
    }

    /// @brief Returns random integer uniform value in range
    /// @tparam int_type integer type of argument and return value.
    /// @param range Range of possible random value.
    /// @return Random integer value.
    template<callisto::framework::concept_integer int_type = int32_t>
    int_type next_int_range(const callisto::math::range<int_type>& range)
    {
        return next_int_range<int_type>(range.min, range.max);
    }

    /// @brief Returns random bool value detemines by probability
    /// @param probability Probability of true value returning.
    /// @return Random bool value.
    bool next_bool(double probability = 0.5)
    {
        auto next_val = next<double>();
        return next_val > probability;
    }
};

} // namespace callisto::utility