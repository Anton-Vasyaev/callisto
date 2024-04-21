#pragma once

// std
#include <cmath>
// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

#include "constants.hpp"

namespace callisto::math
{

template<callisto::framework::concept_arithmetic type>
inline constexpr auto min_f(type value, type min) noexcept
{
    return value < min ? value : min;
}

template<callisto::framework::concept_arithmetic type>
inline constexpr auto max_f(type value, type max) noexcept
{
    return value > max ? value : max;
}

/// @brief Clamps value.
/// @tparam value_type Clamping value type.
/// @tparam min_type Type of min value of clamping.
/// @tparam max_type Type of max value of clamping.
/// @param value Clamping value.
/// @param min_val min value of clamping.
/// @param max_val max value of clamping.
/// @return Clamped value.
template<callisto::framework::concept_arithmetic type>
inline constexpr auto clamp_f(type value, type min_val, type max_val) noexcept
{
    return min_f(max_val, max_f(min_val, value));
}

/// @brief Calculates normalized value (from 0.0 to 1.0) on range.
/// @tparam value_type Type of normalized value.
/// @tparam left_type Type of left border of range.
/// @tparam right_type Type of right border of range.
/// @param value Normalized value.
/// @param left Left border of range.
/// @param right Right border of range.
/// @return Range value.
template<callisto::framework::concept_arithmetic type>
inline constexpr auto norm_on_range(type value, type left, type right) noexcept
{
    return left + value * (right - left);
}

template<callisto::framework::concept_arithmetic type>
inline constexpr auto tmod(type value, type module) noexcept
{
    if constexpr (std::is_floating_point_v<type>)
    {
        return std::fmod(value, module);
    }
    else
    {
        return value % module;
    }
}

template<callisto::framework::concept_arithmetic type>
inline constexpr auto deg2rad(type degree)
{
    return degree / degree_per_radian;
}

template<callisto::framework::concept_arithmetic type>
inline constexpr auto rad2deg(type radian)
{
    return radian / radian_per_degree;
}

} // namespace callisto::math