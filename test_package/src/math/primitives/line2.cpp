#ifndef CALLISTO_MATH_DISABLE

    // test
    #include <callisto/math/primitives/line2.hpp>
    // std
    #include <iostream>
    // 3rd party
    #include <gtest/gtest.h>
    #include <callisto/framework/test/gtest.hpp>
    // project
    #include <math/auxiliary/print_math_data.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

TEST(math_primitives, line2_placeholder_test)
{
    auto line_1 = c_m::line2(243, 20, 157, 13);

    auto line_2 = c_m::line2(243, 20, 157.0f, 13);

    auto line_3 = c_m::line2(243, 12, 256.0f, 1.0);

    auto line_4 = c_m::line2(c_m::point2f(12, 45.5f), c_m::point2d(34, 1.0));

    auto line_5 = c_m::line2(c_m::alg_tuple2(243, 1.4f), c_m::alg_tuple2(12.4f, 2.0));

    c_f::gtest_console::print_line("line_1:", line_1);
    c_f::gtest_console::print_line("line_2:", line_2);
    c_f::gtest_console::print_line("line_3:", line_3);
    c_f::gtest_console::print_line("line_4:", line_4);
    c_f::gtest_console::print_line("line_5:", line_5);

    auto condition_1 = c_m::line2(0, 0, 0, 0) == c_m::line2f::empty();
    auto condition_2 = line_1 != line_3;
    auto condition_3 = line_1 == c_m::line2l(243, 20, 157, 13);
    auto condition_4 = line_1 != c_m::line2l(243, 20, 157, 13);

    c_f::gtest_console::print_line("condition_1:", condition_1);
    c_f::gtest_console::print_line("condition_2:", condition_2);
    c_f::gtest_console::print_line("condition_3:", condition_3);
    c_f::gtest_console::print_line("condition_4:", condition_4);

    ASSERT_EQ(true, true);
}

#endif