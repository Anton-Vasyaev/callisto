#pragma once

// std
#include <cmath>
// 3rd party
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>


namespace callisto::math
{
namespace
{
    namespace c_f = callisto::framework;
}

/// @brief Clamps value.
/// @tparam value_type Clamping value type.
/// @tparam min_type Type of min value of clamping.
/// @tparam max_type Type of max value of clamping.
/// @param value Clamping value.
/// @param min min value of clamping.
/// @param max max value of clamping.
/// @return Clamped value.
template<
    c_f::concept_fundamental value_type,
    c_f::concept_fundamental min_type,
    c_f::concept_fundamental max_type
>
inline constexpr auto clamp(value_type value, min_type min, max_type max) noexcept
{
    using senior_type = c_f::senior_conversion_t<value_type, min_type, max_type>;

    senior_type value_cast = value;
    senior_type min_cast   = min;
    senior_type max_cast   = max;

    return std::clamp(value_cast, min_cast, max_cast);
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
    c_f::concept_fundamental right_type
>
inline constexpr auto norm_on_range(value_type value, left_type left, right_type right) noexcept
{
    return left + value * (right - left);
}

template<
    c_f::concept_fundamental value_type,
    c_f::concept_fundamental min_type
>
inline constexpr auto min(value_type value, min_type min) noexcept
{
    return value < min ? value : min;
}

template<
    c_f::concept_fundamental value_type,
    c_f::concept_fundamental max_type
>
inline constexpr auto max(value_type value, max_type max) noexcept
{
    return value > max ? value : max;
}

}