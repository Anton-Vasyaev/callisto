#pragma once

// std
#include <type_traits>

namespace callisto::framework
{

template<typename type>
constexpr bool is_only_movable_v
    = !std::is_copy_constructible_v<
          type> && std::is_move_constructible_v<type> && !std::is_copy_assignable_v<type> && std::is_move_assignable_v<type>;

template<typename type>
struct is_only_movable
{
    static constexpr bool value = is_only_movable_v<type>;
};

} // namespace callisto::framework