// test
#include <callisto/math/error/relative_error.hpp>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename value_type, typename relative_type, typename result_type>
void relative_error_test_example(value_type value, relative_type relative, result_type result)
{
    auto b_result = c_m::relative_error(value, relative) == result;
    ASSERT_EQ(true, b_result);
}

TEST(math_error, relative_error_test)
{
    relative_error_test_example(273, 0.1, 245.8);
    relative_error_test_example(273, 0.1, 300.2);
    relative_error_test_example(-43, 0.001, -43.0429);
    relative_error_test_example(-43, 0.001, -42.958);
}