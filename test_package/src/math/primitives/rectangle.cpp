// test
#include <callisto/math/primitives/rectangle.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, rectangle_placeholder_test)
{
    auto r = c_m::rectangle_l(23, 25, 100, 200);

    ASSERT_TRUE(r.as<int32_t>() == c_m::rectangle_i(23, 25, 100, 200));
    ASSERT_TRUE(r.center() == c_m::point2l(73, 125));

    r.set_position(c_m::point2l(51, 52));
    r.set_size(c_m::point2l(101, 102));

    ASSERT_TRUE(r == c_m::rectangle_l(51, 52, 101, 102));

    ASSERT_FALSE(r != c_m::rectangle_l(51, 52, 101, 102));
}
