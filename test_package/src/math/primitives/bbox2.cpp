// test
#include <callisto/math/primitives/bbox2.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, bbox2_placeholder_test)
{
    auto a = c_m::bbox2f(0.0, 0.0, 0.0, 0.0);
    ASSERT_TRUE(a.as<int64_t>() == c_m::bbox2l(0, 0, 0, 0));
    ASSERT_TRUE(a.as<int64_t>() != c_m::bbox2l(23, 21, 2, 3));

    auto b = a.as<int64_t>();

    b.set_first(c_m::point2l(-10, -20));
    b.set_second(c_m::point2l(20, 30));

    ASSERT_TRUE(b == c_m::bbox2l(-10, -20, 20, 30));
    ASSERT_TRUE(b.left_top() == c_m::point2l(-10, -20));
    ASSERT_TRUE(b.left_bottom() == c_m::point2l(-10, 30));
    ASSERT_TRUE(b.right_top() == c_m::point2l(20, -20));
    ASSERT_TRUE(b.right_bottom() == c_m::point2l(20, 30));

    ASSERT_TRUE(b.width() == 30);
    ASSERT_TRUE(b.height() == 50);
    ASSERT_TRUE(b.size() == c_m::size2l(30, 50));

    b = a.as<int64_t>();
    ASSERT_TRUE(b == c_m::bbox2l(0, 0, 0, 0));

    b = c_m::bbox2(c_m::point2l(1, 2), c_m::point2l(3, 4));
    ASSERT_TRUE(b == c_m::bbox2l(1, 2, 3, 4));

    auto c = c_m::bbox2(0.0f, 1.0f, 2.0f, 3.0f);
    ASSERT_TRUE(c != c_m::bbox2f(0.01f, 1.0f, 2.0f, 3.0f));
}
