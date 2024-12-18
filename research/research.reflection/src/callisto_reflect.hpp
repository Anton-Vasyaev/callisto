#pragma once

namespace callisto::framework
{

template<typename type>
struct custom_reflection
{
    static constexpr bool exist = false;

    type& ob;

    explicit custom_reflection(type& ob) : ob(ob) {}

    template<typename reflection_type>
    void self_reflect(reflection_type& reflect_ob)
    {
        static_assert("Cannot implement reflection for this type.");
    }
};

} // namespace callisto::framework

// clang-format off

#define CALLISTO_REFLECT(reflect_ob, value)                                                             \
    if constexpr(callisto::framework::custom_reflection<decltype(value)>::exist)                        \
    {                                                                                                   \
        auto custom_reflect_handler = callisto::framework::custom_reflection(value);                    \
        reflect_ob.reflect(custom_reflect_handler, L#value);                                            \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        reflect_ob.reflect(value, L#value);                                                             \
    }
// clang-format on