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
class relative_error
{
public:
    using numeric_type = _numeric_type;

private:
    numeric_type _min;
    numeric_type _max;

public:
    inline constexpr relative_error(numeric_type value, numeric_type percent)
    {
        auto distance = std::abs(value) * percent;
        _min          = value - distance;
        _max          = value + distance;
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
relative_error(value_type, error_type)
    -> relative_error<c_f::senior_conversion_t<value_type, error_type>>;

} // namespace callisto::math