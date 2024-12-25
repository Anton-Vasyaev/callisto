#pragma once

// std
#include <type_traits>

namespace callisto::framework
{

template<typename type>
struct custom_reflection
{
    static constexpr bool exist = false;

    type& data;

    explicit custom_reflection(type& data) : data(data) {}

    template<typename reflection_type>
    void self_reflect(reflection_type& reflect_ob)
    {
        static_assert("Cannot implement reflection for this type.");
    }
};

template<typename type>
struct is_custom_reflection : std::false_type
{
};

template<typename type>
struct is_custom_reflection<custom_reflection<type>> : std::true_type
{
};

template<typename type>
constexpr bool is_custom_reflection_v = is_custom_reflection<type>::value;

template<typename type>
struct enum_reflection
{
    static constexpr bool exist = false;

    static std::array<std::pair<type, std::string_view>, 0>;
};

} // namespace callisto::framework

// clang-format off

#define CALLISTO_REFLECT(reflect_ob, value)                                                             \
    if constexpr(callisto::framework::custom_reflection<decltype(value)>::exist)                        \
    {                                                                                                   \
        auto custom_reflect_handler = callisto::framework::custom_reflection(value);                    \
        reflect_ob.reflect(custom_reflect_handler, L#value, nullptr);                                   \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        reflect_ob.reflect(value, L#value, nullptr);                                                    \
    }


#define CALLISTO_REFLECT_TAGS(reflect_ob, value, __VA_ARGS__)                                           \
    if constexpr(callisto::framework::custom_reflection<decltype(value)>::exist)                        \
    {                                                                                                   \
        auto custom_reflect_handler = callisto::framework::custom_reflection(value);                    \
        reflect_ob.reflect(custom_reflect_handler, L#value, __VA_ARGS__);                               \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        reflect_ob.reflect(value, L#value, __VA_ARGS__);                                                \
    }

// clang-format on