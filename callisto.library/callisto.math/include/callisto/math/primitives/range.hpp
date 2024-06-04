#pragma once

// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct range
{
    using value_type = _value_type;

    value_type min;

    value_type max;

    constexpr range() = default;

    constexpr range(value_type min, value_type max) noexcept
    {
        this->min = min;
        this->max = max;
    }

    // methods
    constexpr auto distance() const noexcept { return this->max - this->min; }

    template<callisto::framework::concept_arithmetic cast_type>
    constexpr auto as() const noexcept
    {
        return range<cast_type>(min, max);
    }
};

template<typename val_type>
range(val_type, val_type) -> range<val_type>;

using range_i = range<int32_t>;
using range_l = range<int64_t>;
using range_f = range<float>;
using range_d = range<double>;

} // namespace callisto::math