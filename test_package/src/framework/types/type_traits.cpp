// test
#include <callisto/framework/types.hpp>
// std
#include <vector>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/native/numeric_type.hpp>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

template<typename type_1, typename type_2, typename result_type>
inline void senior_conversion_test_example()
{
    auto value = std::is_same_v<c_f::senior_conversion_t<type_1, type_2>, result_type>;
    ASSERT_EQ(value, true);
    value = std::is_same_v<typename c_f::senior_conversion<type_1, type_2>::type, result_type>;
    ASSERT_EQ(value, true);

    value = std::is_same_v<c_f::senior_conversion_t<type_2, type_1>, result_type>;
    ASSERT_EQ(value, true);
    value = std::is_same_v<typename c_f::senior_conversion<type_2, type_1>::type, result_type>;
    ASSERT_EQ(value, true);
}

TEST(framework_types, type_traits_senior_conversion_test)
{
    senior_conversion_test_example<int16_t, int64_t, int64_t>();
    senior_conversion_test_example<uint8_t, uint32_t, uint32_t>();
    senior_conversion_test_example<float, uint16_t, float>();
    senior_conversion_test_example<float, int64_t, float>();
    senior_conversion_test_example<float, double, double>();
    senior_conversion_test_example<uint16_t, int32_t, int32_t>();
    senior_conversion_test_example<uint64_t, int8_t, uint64_t>();
    senior_conversion_test_example<uint16_t, uint16_t, uint16_t>();
    senior_conversion_test_example<int32_t, int32_t, int32_t>();
}

template<typename result_type, typename... variadic_types>
inline void senior_conversion_variadic_test_example()
{
    auto value = std::is_same_v<c_f::senior_conversion_t<variadic_types...>, result_type>;
    ASSERT_EQ(value, true);
    value = std::is_same_v<typename c_f::senior_conversion<variadic_types...>::type, result_type>;
    ASSERT_EQ(value, true);
}

TEST(framework_types, type_traits_senior_conversion_test2)
{
    senior_conversion_variadic_test_example<uint16_t, int8_t, uint16_t>();
    senior_conversion_variadic_test_example<int32_t, int8_t, int32_t, uint8_t, int16_t>();
    senior_conversion_variadic_test_example<float, int16_t, float, uint32_t, int32_t, int64_t>();
    senior_conversion_variadic_test_example<
        double,
        uint16_t,
        int16_t,
        double,
        float,
        int32_t,
        uint64_t>();
}

template<typename type, typename... rest_type>
inline void is_any_test_example(bool status)
{
    auto value = c_f::is_any<type, rest_type...>::value;
    ASSERT_EQ(value, status);
    value = c_f::is_any_v<type, rest_type...>;
    ASSERT_EQ(value, status);
}

TEST(framework_types, type_traits_is_any_test)
{
    using float_vector = std::vector<float>;

    is_any_test_example<int, double, float>(false);
    is_any_test_example<bool, uint8_t, uint64_t, bool, std::fstream>(true);
    is_any_test_example<float_vector, double, std::fstream, std::iostream>(false);
    is_any_test_example<float_vector, std::size_t, std::vector<float32_t>>(true);
}