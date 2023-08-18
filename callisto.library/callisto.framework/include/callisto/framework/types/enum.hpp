#pragma once

#include <type_traits>

namespace callisto::framework
{

/// @brief Returns undelying value from enum.
/// @tparam enum_type Type of enum.
/// @param value Value of enum.
/// @return Underlying value.
template<typename enum_type>
inline constexpr auto enum_utype(enum_type value) noexcept
{
    return static_cast<std::underlying_type_t<enum_type>>(value);
}

} // namespace callisto::framework