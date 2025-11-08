#pragma once


namespace callisto::framework
{

template<typename _type>
struct enum_limits
{
    using type = _type;

    static constexpr bool is_specialized = false;

    static constexpr int min_value() { 
        static_assert("is not specialized");
        return 0; }

    static constexpr int max_value() { 
        static_assert("is not specialized");
    return 0; }
};

}