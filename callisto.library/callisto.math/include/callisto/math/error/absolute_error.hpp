#pragma once

// std
#include <cmath>
// 3rd party
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

// imports
namespace
{
namespace c_f = callisto::framework;
}

template<typename _numeric_type>
class absolute_error
{
public:
    using numeric_type = _numeric_type;

private:
    numeric_type _min;
    numeric_type _max;

public:
    inline constexpr absolute_error(numeric_type value, numeric_type error)
    {
        _min = value - error;
        _max = value + error;
    }

    template<typename other_type>
    inline constexpr bool operator==(other_type value)
    {
        return _min < value && value < _max;
    }

    template<typename other_type>
    inline constexpr bool operator!=(other_type value)
    {
        return value < _min || _max < value;
    }
};

template<typename value_type, typename error_type>
absolute_error(value_type, error_type)
    -> absolute_error<c_f::senior_conversion_t<value_type, error_type>>;

} // namespace callisto::math