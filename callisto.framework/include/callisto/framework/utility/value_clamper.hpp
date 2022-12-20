#pragma once

// std
#include <algorithm>
// 3rd party
#include <callisto/framework/concepts.hpp>

namespace callisto::framework
{

/// @brief Provides automatically value clamping on assignment.
/// @tparam _value_type Arithmetic data type of clamped value.
template<concept_arithmetic _value_type>
class value_clamper
{
public:
    using value_type = _value_type;

private:
    value_type _value;

    value_type _min;

    value_type _max;

    inline void set_value(value_type other_value)
    {
        _value = std::clamp<value_type>(other_value, _min, _max);
    }

public:
    /// @brief Constructs a new value clamper.
    inline value_clamper() {}

    /// @brief Constructs a new value clamper.
    /// @param value Fixed value.
    /// @param min   Min value of clamping.
    /// @param max   Max value of clamping.
    inline value_clamper(value_type value, value_type min, value_type max)
    {
        _min = min;
        _max = max;

        set_value(value);
    }

    /// @brief operator=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_clamper&
    template<typename other_value_type>
    inline value_clamper& operator=(other_value_type v)
    {
        set_value(v);

        return *this;
    }

    /// @brief operator+=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_clamper&
    template<typename other_value_type>
    inline value_clamper& operator+=(other_value_type v)
    {
        set_value(_value + v);

        return *this;
    }

    /// @brief operator-=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_clamper&
    template<typename other_value_type>
    inline value_clamper& operator-=(other_value_type v)
    {
        set_value(_value - v);

        return *this;
    }

    /// @brief operator*=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_clamper&
    template<typename other_value_type>
    inline value_clamper& operator*=(other_value_type v)
    {
        set_value(_value * v);

        return *this;
    }

    /// @brief operator/=
    /// @tparam other_value_type
    /// @param v Value.
    /// @return value_clamper&
    template<typename other_value_type>
    inline value_clamper& operator/=(other_value_type v)
    {
        set_value(_value / v);

        return *this;
    }

    /// @brief casting operator to @ref value_type.
    inline operator value_type() const { return _value; }
};

} // namespace callisto::framework