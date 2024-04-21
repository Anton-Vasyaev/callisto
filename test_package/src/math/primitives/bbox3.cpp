// test
#include <callisto/math/primitives/bbox3.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, bbox3_placeholder_test)
{
    auto a = c_m::bbox3f(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    ASSERT_TRUE(a.as<int64_t>() == c_m::bbox3l(0, 0, 0, 0, 0, 0));
    ASSERT_TRUE(a.as<int64_t>() != c_m::bbox3l(23, 21, 2, 3, 1, 2));

    auto b = a.as<int64_t>();

    b.set_first(c_m::point3l(-10, -20, 10));
    b.set_second(c_m::point3l(20, 30, 25));

    ASSERT_TRUE(b == c_m::bbox3l(-10, -20, 10, 20, 30, 25));
    ASSERT_TRUE(b.left_top_near() == c_m::point3l(-10, -20, 10));
    ASSERT_TRUE(b.left_bottom_near() == c_m::point3l(-10, 30, 10));
    ASSERT_TRUE(b.right_top_near() == c_m::point3l(20, -20, 10));
    ASSERT_TRUE(b.right_bottom_near() == c_m::point3l(20, 30, 10));

    ASSERT_TRUE(b.left_top_far() == c_m::point3l(-10, -20, 25));
    ASSERT_TRUE(b.left_bottom_far() == c_m::point3l(-10, 30, 25));
    ASSERT_TRUE(b.right_top_far() == c_m::point3l(20, -20, 25));
    ASSERT_TRUE(b.right_bottom_far() == c_m::point3l(20, 30, 25));

    ASSERT_TRUE(b.width() == 30);
    ASSERT_TRUE(b.height() == 50);
    ASSERT_TRUE(b.depth() == 15);
    ASSERT_TRUE(b.size() == c_m::size3l(30, 50, 15));

    b = a.as<int64_t>();
    ASSERT_TRUE(b == c_m::bbox3l(0, 0, 0, 0, 0, 0));

    b = c_m::bbox3(c_m::point3l(1, 2, 3), c_m::point3l(4, 5, 6));
    ASSERT_TRUE(b == c_m::bbox3l(1, 2, 3, 4, 5, 6));

    auto c = c_m::bbox3(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    ASSERT_TRUE(c != c_m::bbox3f(0.01f, 1.0f, 2.0f, 3.0f, -3.0f, 1.0f));
}