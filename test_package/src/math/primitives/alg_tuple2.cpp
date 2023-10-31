// test
#include <callisto/math/primitives/alg_tuple2.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename point2_type>
void print_point2(const point2_type& line)
{
    c_f::gtest_console::print_line("[", line.v1, ", ", line.v2, "]");
}

TEST(math_primitives, alg_tuple2_placeholder_test)
{
    auto p1 = c_m::point2f(243, 674);

    p1        = c_m::point2l(123, 32);
    p1.v1     = 23;
    p1.v2     = 32;
    p1.x      = 23;
    p1.y      = 32;
    p1.width  = 23;
    p1.height = 32;
    p1 /= 23;
    p1 *= 21;
    p1 += 133.0;
    p1 -= 13.4;
    c_f::gtest_console::print_line("p1:", p1);

    p1 = c_m::vector2f(23.45, 123.4) / c_m::size2l(240, 534);
    c_f::gtest_console::print_line("p1:", p1);

    auto p2 = c_m::vector2f(23.45, 123.4) * c_m::point2d(1.543, 0.45);
    c_f::gtest_console::print_line("p2:", p2);

    auto p3 = c_m::vector2<uint8_t>(15, 64) * 0.3445f;
    c_f::gtest_console::print_line("p3:", p3);

    auto size_1 = c_m::size2l(1024, 1024);
    auto p4     = c_m::point2i(512, 512) / (size_1 * 1.0);
    c_f::gtest_console::print_line("p4:", p4);

    auto p5 = c_m::alg_tuple2(1024, 1024.0);
    p5 += 0.5f;
    c_f::gtest_console::print_line("p5:", p5);

    auto condition_1 = c_m::point2i(102, 66) == c_m::point2l(102, 66);
    auto condition_2 = c_m::point2l(0, 0) == c_m::point2l::empty();
    auto condition_3 = c_m::point2f(0.0f, 0.0f) == c_m::point2f::empty();
    auto condition_4 = c_m::point2l(102, 36) != c_m::point2l(36, 102);
    auto condition_5 = c_m::point2l(102, 36) != c_m::point2<uint8_t>(102, 36);

    c_f::gtest_console::print_line("condition_1:", condition_1);
    c_f::gtest_console::print_line("condition_2:", condition_2);
    c_f::gtest_console::print_line("condition_3:", condition_3);
    c_f::gtest_console::print_line("condition_4:", condition_4);
    c_f::gtest_console::print_line("condition_5:", condition_5);

    ASSERT_EQ(true, true);
}
