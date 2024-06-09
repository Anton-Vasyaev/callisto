// test
#include <callisto/math/primitives/alg_tuple3.hpp>
// project
#include <math/auxiliary/print_math_data.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename point2_type>
void print_point2(const point2_type& line)
{
    c_f::gtest_console::print_line("[", line.v1, ", ", line.v2, "]");
}

TEST(math_primitives, alg_tuple3_placeholder_test)
{
    auto p1 = c_m::point3f(243, 674, 342);

    p1        = c_m::point3l(123, 32, 21).as<float>();
    p1.v1     = 23;
    p1.v2     = 32;
    p1.x      = 23;
    p1.y      = 32;
    p1.width  = 23;
    p1.height = 32;

    p1 = -p1;

    p1 /= 23;
    p1 /= c_m::size3f(24.0, 25.0, 26.0);

    p1 *= 21;
    p1 *= c_m::size3f(21, 21, 21);

    p1 += 133.0;
    p1 -= c_m::point3l(1024, 1024, 1024).as<float>();

    p1 -= 13.4;
    p1 -= c_m::point3d(23.0, 23.0, 23.0).as<float>();

    c_f::gtest_console::print_line("p1:", p1);

    p1 = c_m::vector3f(23.45, 123.4, 120.5) / c_m::size3l(240, 534, 33).as<float>();
    p1 = p1 / 1.2;
    c_f::gtest_console::print_line("p1:", p1);

    auto p2 = c_m::vector3f(23.45, 123.4, 56.77).as<double>() * c_m::point3d(1.543, 0.45, 3.43);
    p2      = p2 * 1.1;
    c_f::gtest_console::print_line("p2:", p2);

    auto p3 = c_m::vector3<uint8_t>(15, 64, 21) * static_cast<uint8_t>(2);
    c_f::gtest_console::print_line("p3:", p3);

    auto size_1 = c_m::size3l::from_scalar(1024);
    auto p4     = c_m::point3i::from_scalar(512) / (size_1.as<int>() * 1.0);
    c_f::gtest_console::print_line("p4:", p4);

    auto p5 = c_m::point3d::from_scalar(1024);
    p5 += 0.5F;
    c_f::gtest_console::print_line("p5:", p5);

    auto p6 = c_m::point3d::from_scalar(512) - c_m::point3f(12.0, 15.0, 16.0).as<double>();
    p6      = p6 - 20.0;
    c_f::gtest_console::print_line("p6:", p6);

    auto condition_1 = c_m::point3i(102, 66, 21) == c_m::point3i(102, 66, 21);
    auto condition_2 = c_m::point3l(0, 0, 0) == c_m::point3l::empty();
    auto condition_3 = c_m::point3f(0.0, 0.0, 0.0) == c_m::point3f::empty();
    auto condition_4 = c_m::point3l(102, 36, 21) != c_m::point3l(36, 102, 21);
    auto condition_5 = c_m::point3l(102, 36, 22) != c_m::point3l(102, 36, 22);

    c_f::gtest_console::print_line("condition_1:", condition_1);
    c_f::gtest_console::print_line("condition_2:", condition_2);
    c_f::gtest_console::print_line("condition_3:", condition_3);
    c_f::gtest_console::print_line("condition_4:", condition_4);
    c_f::gtest_console::print_line("condition_5:", condition_5);

    ASSERT_EQ(true, true);
}
