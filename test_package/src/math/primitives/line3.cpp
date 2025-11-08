// test
#include <callisto/math/primitives/line3.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_m = callisto::math;

TEST(math_primitives, line3_placeholder_test)
{
    auto a = c_m::line3f(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    ASSERT_TRUE(a.as<int64_t>() == c_m::line3l(0, 0, 0, 0, 0, 0));
    ASSERT_TRUE(a.as<int64_t>() != c_m::line3l(23, 21, 2, 3, 4, 5));

    auto b = a.as<int64_t>();

    b.set_first(c_m::point3l(-10, -20, -30));
    b.set_second(c_m::point3l(20, 30, 40));

    ASSERT_TRUE(b == c_m::line3l(-10, -20, -30, 20, 30, 40));
    ASSERT_TRUE(b.first() == c_m::point3l(-10, -20, -30));
    ASSERT_TRUE(b.second() == c_m::point3l(20, 30, 40));

    ASSERT_TRUE(b.center() == c_m::point3l(5, 5, 5));

    b = a.as<int64_t>();
    ASSERT_TRUE(b == c_m::line3l(0, 0, 0, 0, 0, 0));

    b = c_m::line3(c_m::point3l(1, 2, 3), c_m::point3l(4, 5, 6));
    ASSERT_TRUE(b == c_m::line3l(1, 2, 3, 4, 5, 6));

    auto c = c_m::line3(0.0F, 1.0F, 2.0F, 3.0F, 4.0F, 5.0F);
    ASSERT_TRUE(c != c_m::line3f(0.01, 1.0, 2.0, 3.0, 0.01, 0.0));
}
