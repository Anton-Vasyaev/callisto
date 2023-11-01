#pragma once

// std
#include <type_traits>

namespace callisto::framework
{

template<typename type, typename... rest_type>
struct is_any : std::false_type
{
};

template<typename type, typename first_type>
struct is_any<type, first_type> : std::is_same<type, first_type>
{
};

template<typename type, typename first_type, typename... rest_type>
struct is_any<type, first_type, rest_type...> :
    std::integral_constant<
        bool,
        std::is_same<type, first_type>::value || is_any<type, rest_type...>::value>
{
};

template<typename type, typename... rest_type>
constexpr bool is_any_v = (std::is_same_v<type, rest_type> || ...);

} // namespace callisto::framework
