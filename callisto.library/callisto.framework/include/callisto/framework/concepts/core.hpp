#pragma once

// std
#include <concepts>
#include <type_traits>

namespace callisto::framework
{

/// @brief Sets the constraint: type must be arithmetic.
template<typename type>
concept concept_arithmetic = std::is_arithmetic_v<type>;

/// @brief Sets the constraint: type must be fundamental.
template<typename type>
concept concept_fundamental = std::is_fundamental_v<type>;

/// @brief Sets the constraint: type must be integer.
template<typename type>
concept concept_integer = std::is_integral_v<type>;

/// @brief sets the constraint: type must be floating point.
template<typename type>
concept concept_floating_point = std::is_floating_point_v<type>;

/// @brief Sets the constraint: type must be enum or enum class.
template<typename type>
concept concept_enum = std::is_enum_v<type>;

} // namespace callisto::framework