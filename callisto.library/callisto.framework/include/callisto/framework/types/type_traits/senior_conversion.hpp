#pragma once

// project
#include <callisto/framework/concepts/core.hpp>

namespace callisto::framework
{

template<concept_arithmetic type_1, concept_arithmetic type_2>
struct __senior_conversion_integral_same_size__
{
    using type = std::conditional_t<std::is_signed_v<type_1>, type_1, type_2>;
};

template<concept_arithmetic type_1, concept_arithmetic type_2>
using __senior_conversion_integral_same_size_t__ 
    = typename __senior_conversion_integral_same_size__<type_1, type_2>::type;



template<concept_arithmetic type_1, concept_arithmetic type_2>
struct __senior_conversion_integral_diff_size__
{
    using type = std::conditional_t<(sizeof(type_1) > sizeof(type_2)), type_1, type_2>;
};

template<concept_arithmetic type_1, concept_arithmetic type_2>
using __senior_conversion_integral_diff_size_t__ 
    = typename __senior_conversion_integral_diff_size__<type_1, type_2>::type;



template<concept_arithmetic type_1, concept_arithmetic type_2>
struct __senior_conversion_integral__
{
    using type = std::conditional_t<
        (sizeof(type_1) == sizeof(type_2)),
        __senior_conversion_integral_same_size_t__<type_1, type_2>,
        __senior_conversion_integral_diff_size_t__<type_1, type_2>
    >;
};

template<concept_arithmetic type_1, concept_arithmetic type_2>
using __senior_conversion_integral_t__ 
    = typename __senior_conversion_integral__<type_1, type_2>::type;



template<concept_arithmetic type_1, concept_arithmetic type_2>
struct __senior_conversion_floating_point__
{
    using type = std::conditional_t<(sizeof(type_1) >= sizeof(type_2)), type_1, type_2>;
};

template<concept_arithmetic type_1, concept_arithmetic type_2>
using __senior_conversion_floating_point_t__
    = typename __senior_conversion_floating_point__<type_1, type_2>::type;



template<concept_arithmetic type_1, concept_arithmetic type_2>
struct __senior_conversion_same_fundament__
{
    using type = std::conditional_t<
        std::is_floating_point_v<type_1> && std::is_floating_point_v<type_2>,
        __senior_conversion_floating_point_t__<type_1, type_2>,
        __senior_conversion_integral_t__<type_1, type_2>
    >;
};

template<concept_arithmetic type_1, concept_arithmetic type_2>
using __senior_conversion_same_fundament_t__
    = typename __senior_conversion_same_fundament__<type_1, type_2>::type;



template<concept_arithmetic type_1, concept_arithmetic type_2>
struct __senior_conversion_diff_fundament__
{
    using type = std::conditional_t<std::is_floating_point_v<type_1>, type_1, type_2>;
};

template<concept_arithmetic type_1, concept_arithmetic type_2>
using __senior_conversion_diff_fundament_t__
    = typename __senior_conversion_diff_fundament__<type_1, type_2>::type;


template<concept_arithmetic... rest_type>
struct senior_conversion { };


template<concept_arithmetic type_1, concept_arithmetic type_2> 
struct senior_conversion<type_1, type_2>
{
    using type = std::conditional_t<
        (
            (std::is_integral_v<type_1>       && std::is_floating_point_v<type_2>) ||
            (std::is_floating_point_v<type_1> && std::is_integral_v<type_2>)
        ),
        __senior_conversion_diff_fundament_t__<type_1, type_2>,
        __senior_conversion_same_fundament_t__<type_1, type_2>
    >;
};


template<concept_arithmetic type_1, concept_arithmetic type_2, concept_arithmetic... rest_type>
struct senior_conversion<type_1, type_2, rest_type...>
{
private:
    using _recursive_type = typename senior_conversion<type_2, rest_type...>::type;

public:
    using type = typename senior_conversion<type_1, _recursive_type>::type;
};

template<concept_arithmetic... rest_type>
using senior_conversion_t = typename senior_conversion<rest_type...>::type;

}