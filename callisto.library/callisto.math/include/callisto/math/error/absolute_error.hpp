#pragma once

// std
#include <cmath>
// 3rd party
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

template<typename _numeric_type>
class absolute_error
{
public:
    using numeric_type = _numeric_type;

private:
    numeric_type _min;
    numeric_type _max;

public:
    constexpr absolute_error(numeric_type value, numeric_type error)
    {
        _min = value - error;
        _max = value + error;
    }

    template<typename other_type>
    constexpr bool operator==(other_type value)
    {
        return _min < value && value < _max;
    }

    template<typename other_type>
    constexpr bool operator!=(other_type value)
    {
        return value < _min || _max < value;
    }
};

template<typename value_type>
absolute_error(value_type, value_type) -> absolute_error<value_type>;

} // namespace callisto::math