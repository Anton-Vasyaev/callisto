// test
#include <callisto/math/functions.hpp>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>
// project
#include <callisto/math/primitives.hpp>
#include <callisto/math/error/relative_error.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename numeric_type>
using err = c_m::relative_error<numeric_type>;

TEST(math_functions, functions_placeholder_test_1)
{
    constexpr auto clamp_val = c_m::clamp_f(1.3, 1, 2);

    constexpr auto min_val = c_m::min_f(5.0, 6.0);

    constexpr auto max_val = c_m::max_f(23.0, 17.0);

    ASSERT_EQ(true, true);
}