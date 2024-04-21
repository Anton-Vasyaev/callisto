// test
#include <callisto/math/primitives/line2.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, line2_placeholder_test)
{
    auto a = c_m::line2f(0.0, 0.0, 0.0, 0.0);
    ASSERT_TRUE(a.as<int64_t>() == c_m::line2l(0, 0, 0, 0));
    ASSERT_TRUE(a.as<int64_t>() != c_m::line2l(23, 21, 2, 3));

    auto b = a.as<int64_t>();

    b.set_first(c_m::point2l(-10, -20));
    b.set_second(c_m::point2l(20, 30));

    ASSERT_TRUE(b == c_m::line2l(-10, -20, 20, 30));
    ASSERT_TRUE(b.first() == c_m::point2l(-10, -20));
    ASSERT_TRUE(b.second() == c_m::point2l(20, 30));

    ASSERT_TRUE(b.center() == c_m::point2l(5, 5));

    b = a.as<int64_t>();
    ASSERT_TRUE(b == c_m::line2l(0, 0, 0, 0));

    b = c_m::line2(c_m::point2l(1, 2), c_m::point2l(3, 4));
    ASSERT_TRUE(b == c_m::line2l(1, 2, 3, 4));

    auto c = c_m::line2(0.0f, 1.0f, 2.0f, 3.0f);
    ASSERT_TRUE(c != c_m::line2f(0.01f, 1.0f, 2.0f, 3.0f));
}
