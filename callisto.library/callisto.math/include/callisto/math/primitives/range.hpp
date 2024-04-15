#pragma once

// project
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

namespace
{
namespace c_f = callisto::framework;
}

template<typename _type>
struct range
{
    using type = _type;

    type min;

    type max;

    inline constexpr range() {}

    template<typename min_type, typename max_type>
    inline constexpr range(min_type min, max_type max) noexcept
    {
        this->min = static_cast<type>(min);

        this->max = static_cast<type>(max);
    }

    // methods
    inline constexpr auto distance() const noexcept { return this->max - this->min; }
};

template<typename min_type, typename max_type>
range(min_type, max_type) -> range<c_f::senior_conversion_t<min_type, max_type>>;

using range_i = range<int32_t>;
using range_l = range<int64_t>;
using range_f = range<float>;
using range_d = range<double>;

} // namespace callisto::math