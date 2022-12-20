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

template<typename numeric_type>
class relative_error
{
    numeric_type min;
    numeric_type max;

public:
    inline constexpr relative_error(numeric_type value, numeric_type percent)
    {
        auto distance = std::abs(value) * percent;
        this->min     = value - distance;
        this->max     = value + distance;
    }

    template<typename other_type>
    inline constexpr bool operator==(other_type value)
    {
        return this->min < value && value < this->max;
    }

    template<typename other_type>
    inline constexpr bool operator!=(other_type value)
    {
        return value < this->min || this->max < value;
    }
};

template<typename type_1, typename type_2>
relative_error(type_1, type_2) -> relative_error<c_f::senior_conversion_t<type_1, type_2>>;

} // namespace callisto::math