#pragma once

// std
#include <cmath>
// 3rd party
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

template<typename numeric_type_t>
class relative_error
{
public:
    using numeric_type = numeric_type_t;

private:
    numeric_type __min;
    numeric_type __max;

public:
    constexpr relative_error(numeric_type value, numeric_type percent)
    {
        auto distance = std::abs(value) * percent;
        __min         = value - distance;
        __max         = value + distance;
    }

    template<typename other_type>
    constexpr bool operator==(other_type value)
    {
        return __min < value && value < __max;
    }

    template<typename other_type>
    constexpr bool operator!=(other_type value)
    {
        return value < __min || __max < value;
    }
};

template<typename value_type>
relative_error(value_type, value_type) -> relative_error<value_type>;

} // namespace callisto::math