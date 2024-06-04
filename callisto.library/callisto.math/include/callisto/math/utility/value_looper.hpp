#pragma once

// project
#include <callisto/framework/concepts.hpp>

#include <callisto/math/functions.hpp>

namespace callisto::math
{

/// @brief Provides automatically value looping on assignment.
/// @tparam _value_type Arithmetic data type of looped value.
template<callisto::framework::concept_arithmetic _value_type>
class value_looper
{
public:
    using value_type = _value_type;

private:
    value_type __value;

    value_type __start;

    value_type __size;

    constexpr void __set_value(value_type value)
    {
        value        = value - __start;
        auto mod_res = tmod(value, __size);
        __value      = mod_res > 0.0 ? __start + mod_res : __start + __size + mod_res;
    }

public:
    constexpr value_looper() = default;

    /// @brief Constructs a new value looper.
    /// @param value Loop value.
    /// @param start Start of loop.
    /// @param end End of loop.
    constexpr value_looper(value_type value, value_type start, value_type end)
    {
        __value = value;
        __start = start;
        __size  = end - start;
    }

    constexpr value_type value() const noexcept { return __value; }

    /// @brief operator=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr value_looper& operator=(other_value_type v)
    {
        __set_value(v);

        return *this;
    }

    /// @brief operator+=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr value_looper& operator+=(other_value_type v)
    {
        __set_value(__value + v);

        return *this;
    }

    /// @brief operator-=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr value_looper& operator-=(other_value_type v)
    {
        __set_value(__value - v);

        return *this;
    }

    /// @brief operator*=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr value_looper& operator*=(other_value_type v)
    {
        __set_value(__value * v);

        return *this;
    }

    /// @brief operator/=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr value_looper& operator/=(other_value_type v)
    {
        __set_value(__value / v);

        return *this;
    }
};

} // namespace callisto::math