// test
#include <callisto/math/primitives/range.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

#include <callisto/math/error/relative_error.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, range_placeholder_test)
{
    auto r = c_m::range_f(0.0f, 1.0f);

    ASSERT_TRUE(c_m::relative_error(r.distance(), 1e-6) == 1.0f);

    auto r_l = r.as<int64_t>();

    ASSERT_TRUE(r_l.min == 0);
    ASSERT_TRUE(r_l.max == 1);
}
