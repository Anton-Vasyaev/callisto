// test
#include <callisto/math/operations/vector2op.hpp>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>
// project
#include <callisto/math/primitives.hpp>
#include <callisto/math/error/relative_error.hpp>

#include <math/auxiliary/print_math_data.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename numeric_type>
using err = c_m::relative_error<numeric_type>;

using vec2 = c_m::vector2op;

using out = c_f::gtest_console;

TEST(math_operations, vector2_operations_placeholder_test)
{
    auto vec1i = c_m::vector2i { 34, 56 };
    auto vec2i = c_m::vector2i { 54, 71 };

    auto result_i   = vec2::normalize(vec1i, 100);
    auto result_d2i = (c_m::vector2i)vec2::normalize<double>(vec1i, 100);
    result_d2i      = vec2::normalize<float>(vec1i, 100);
    auto result_d   = vec2::normalize(c_m::vector2d(vec1i), 100);

    out::print_line("result integer, calc_type = void   :", result_i);
    out::print_line("result integer, calc_type = double :", result_d2i);
    out::print_line("result double,  calc_type = void   :", result_d);
    out::print_line("");

    auto vec1f = c_m::vector2f { 0.34, 0.56 };
    auto vec2f = c_m::vector2f { -0.54, 0.71 };

    out::print_line("vec1:", vec1f, ", vec2:", vec2f);
    out::print_line("vec1 - square_of_length:               ", vec2::square_of_length(vec1f));
    out::print_line("vec1 - length:                         ", vec2::length(vec1f));
    out::print_line("vec1 - normalize:                      ", vec2::normalize(vec1f));
    out::print_line("vec1 & vec2 - dot_product:             ", vec2::dot_product(vec1f, vec2f));
    out::print_line("vec1 & vec2 - cos_angle:               ", vec2::cos_angle(vec1f, vec2f));
    out::print_line("vec1 & vec2 - angle:                   ", vec2::angle(vec1f, vec2f));
    out::print_line("vec1 & vec2 - sign_angle:              ", vec2::sign_angle(vec1f, vec2f));
    out::print_line(
        "vec1 & vec2 - pseudo_scalar_product:   ",
        vec2::pseudo_scalar_product(vec1f, vec2f)
    );

    out::print_line("angle between vec1 and vec2:", vec2::angle(vec1f, vec2f));
    out::print_line();

    ASSERT_EQ(true, true);
}