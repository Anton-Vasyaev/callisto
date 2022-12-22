#pragma once

#include <type_traits>

namespace callisto::math
{

template<typename calc_type, typename value_type>
struct calc_type_selection
{
    using type = std::conditional_t<std::is_void_v<calc_type>, value_type, calc_type>;
};

template<typename calc_type, typename value_type>
using calc_type_selection_t = typename calc_type_selection<calc_type, value_type>::type;
} // namespace callisto::math