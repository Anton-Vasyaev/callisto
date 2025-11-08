#pragma once

// std
#include <algorithm>
// 3rd party
#include <callisto/framework/concepts.hpp>

namespace callisto::math
{

/// @brief Provides automatically value clamping on assignment.
/// @tparam _value_type Arithmetic data type of clamped value.
template<callisto::framework::concept_arithmetic _value_type>
class value_clamper
{
public:
    using value_type = _value_type;

private:
    value_type __value;

    value_type __min;

    value_type __max;

    constexpr void set_value(value_type other_value)
    {
        __value = std::clamp<value_type>(other_value, __min, __max);
    }

public:
    /// @brief Constructs a new value clamper.
    constexpr value_clamper() = default;

    /// @brief Constructs a new value clamper.
    /// @param value Fixed value.
    /// @param min   Min value of clamping.
    /// @param max   Max value of clamping.
    constexpr value_clamper(value_type value, value_type min, value_type max)
    {
        __min = min;
        __max = max;

        set_value(value);
    }

    /// @brief Returns value.
    /// @return value.
    constexpr value_type value() const noexcept { return __value; }

    /// @brief operator=
    /// @param v Value.
    /// @return value_clamper&
    constexpr value_clamper& operator=(value_type v) noexcept
    {
        set_value(v);

        return *this;
    }

    /// @brief operator+=
    /// @param v Value.
    /// @return value_clamper&
    constexpr value_clamper& operator+=(value_type v) noexcept
    {
        set_value(__value + v);

        return *this;
    }

    /// @brief operator-=
    /// @param v Value.
    /// @return value_clamper&
    constexpr value_clamper& operator-=(value_type v) noexcept
    {
        set_value(__value - v);

        return *this;
    }

    /// @brief operator*=
    /// @param v Value.
    /// @return value_clamper&
    constexpr value_clamper& operator*=(value_type v) noexcept
    {
        set_value(__value * v);

        return *this;
    }

    /// @brief operator/=
    /// @param v Value.
    /// @return value_clamper&
    constexpr value_clamper& operator/=(value_type v) noexcept
    {
        set_value(__value / v);

        return *this;
    }
};

} // namespace callisto::math