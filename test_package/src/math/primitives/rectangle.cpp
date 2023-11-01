// test
#include <callisto/math/primitives/rectangle.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, rectangle_placeholder_test)
{
    auto rect_1 = c_m::rectangle(0, 0, 243, 341);

    auto rect_2 = c_m::rectangle(12, 15, 168.0f, 240.0);

    auto rect_3 = c_m::rectangle(c_m::point2i(20, 30), c_m::size2d(11.3, 14.5f));

    auto rect_4 = c_m::rectangle(c_m::alg_tuple2(20, 30), c_m::alg_tuple2(11.0, 14.0f));

    c_f::gtest_console::print_line("rect_1", rect_1);
    c_f::gtest_console::print_line("rect_2", rect_2);
    c_f::gtest_console::print_line("rect_3", rect_3);

    auto condition_1 = c_m::rectangle_f(0, 0, 0, 0) == c_m::rectangle_l::empty();
    auto condition_2 = c_m::rectangle(0, 0, 243.0f, 123.f) != rect_4;
    auto condition_3 = c_m::rectangle(0, 0, 243, 341) != rect_1;

    c_f::gtest_console::print_line("condition_1:", condition_1);
    c_f::gtest_console::print_line("condition_2:", condition_2);
    c_f::gtest_console::print_line("condition_3:", condition_3);

    ASSERT_EQ(true, true);
}
