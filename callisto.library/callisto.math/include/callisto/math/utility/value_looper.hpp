#pragma once

// project
#include <callisto/framework/concepts.hpp>

#include <callisto/math/functions.hpp>

namespace callisto::math
{

namespace
{
    namespace c_f = callisto::framework;
}

/// @brief Provides automatically value looping on assignment.
/// @tparam _value_type Arithmetic data type of looped value.
template<c_f::concept_arithmetic _value_type>
class value_looper
{
public:
    using value_type = _value_type;

private:
    value_type _value;
    
    value_type _start;
    
    value_type _size;

    constexpr inline void set_value(value_type value)
    {
        auto mod_res = tmod(value, _size);
        _value = mod_res < 0 ? _size - mod_res : mod_res;
    }
public:
    constexpr inline value_looper() { }

    /// @brief Constructs a new value looper.
    /// @param value Loop value.
    /// @param start Start of loop.
    /// @param end End of loop.
    constexpr inline value_looper(
        value_type value,
        value_type start,
        value_type end
    )
    {
        _value = value;
        _start = start;
        _size = end - start;
    }

        /// @brief operator=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr inline value_looper& operator=(other_value_type v)
    {
        set_value(v);

        return *this;
    }

    /// @brief operator+=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr inline value_looper& operator+=(other_value_type v)
    {
        set_value(_value + v);

        return *this;
    }

    /// @brief operator-=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr inline value_looper& operator-=(other_value_type v)
    {
        set_value(_value - v);

        return *this;
    }

    /// @brief operator*=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr inline value_looper& operator*=(other_value_type v)
    {
        set_value(_value * v);

        return *this;
    }

    /// @brief operator/=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_looper&
    template<typename other_value_type>
    constexpr inline value_looper& operator/=(other_value_type v)
    {
        set_value(_value / v);

        return *this;
    }

    /// @brief casting operator to @ref value_type.
    constexpr inline operator value_type() const { return _value; }
};


}