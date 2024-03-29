#pragma once

// std
#include <cmath>
// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

#include "constants.hpp"

namespace callisto::math
{
namespace
{
namespace c_f = callisto::framework;
}

template<c_f::concept_fundamental value_type, c_f::concept_fundamental min_type>
inline constexpr auto min_f(value_type value, min_type min) noexcept
{
    return value < min ? value : min;
}

template<c_f::concept_fundamental value_type, c_f::concept_fundamental max_type>
inline constexpr auto max_f(value_type value, max_type max) noexcept
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
template<
    c_f::concept_fundamental value_type,
    c_f::concept_fundamental min_type,
    c_f::concept_fundamental max_type>
inline constexpr auto clamp_f(value_type value, min_type min_val, max_type max_val) noexcept
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
template<
    c_f::concept_fundamental value_type,
    c_f::concept_fundamental left_type,
    c_f::concept_fundamental right_type>
inline constexpr auto norm_on_range(value_type value, left_type left, right_type right) noexcept
{
    return left + value * (right - left);
}

template<c_f::concept_fundamental value_type, c_f::concept_fundamental mod_type>
inline constexpr auto tmod(value_type value, mod_type module) noexcept
{
    if constexpr (std::is_floating_point_v<c_f::senior_conversion_t<value_type, mod_type>>)
    {
        return std::fmod(value, module);
    }
    else
    {
        return value % module;
    }
}

template<c_f::concept_fundamental value_type>
inline constexpr auto deg2rad(value_type degree)
{
    return degree / degree_per_radian;
}

template<c_f::concept_fundamental value_type>
inline constexpr auto rad2deg(value_type radian)
{
    return radian / radian_per_degree;
}

} // namespace callisto::math