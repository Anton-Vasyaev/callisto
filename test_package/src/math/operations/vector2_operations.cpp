// test
#include <callisto/math/operations/vector2op.hpp>
// 3rd party
#include <gtest/gtest.h>

// project
#include <callisto/framework/test/gtest.hpp>
#include <callisto/math/primitives.hpp>
#include <callisto/math/error.hpp>
#include <callisto/math/operations/point2op.hpp>
#include <callisto/math/constants.hpp>

#include <math/auxiliary/print_math_data.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename numeric_type>
using err = c_m::relative_error<numeric_type>;

using vec2 = c_m::vector2op;
using p2   = c_m::point2op;

using out = c_f::gtest_console;

constexpr double rel_double_acc = 1e-6;
constexpr double abs_double_acc = 1e-6;

constexpr float rel_float_acc = 1e-4;
constexpr float abs_float_acc = 1e-4;

TEST(vector2_operations, square_of_length_test)
{
    auto vec        = c_m::vector2d(5, 6);
    auto square_len = vec2::square_of_length(vec);
    ASSERT_TRUE(c_m::relative_error(square_len, rel_double_acc) == 61.0);

    vec        = c_m::vector2d(-5, -6);
    square_len = vec2::square_of_length(vec);
    ASSERT_TRUE(c_m::relative_error(square_len, rel_double_acc) == 61.0);
}

TEST(vector2_operations, length_test)
{
    auto vec = c_m::vector2d(85, 132);
    auto len = vec2::length(vec);
    ASSERT_TRUE(c_m::relative_error(len, rel_double_acc) == 157.0);

    vec = c_m::vector2d(-85, 132);
    len = vec2::length(vec);
    ASSERT_TRUE(c_m::relative_error(len, rel_double_acc) == 157.0);
}

TEST(vector2_operations, normalize_test)
{
    auto vec_d    = c_m::vector2d(44, 534);
    auto norm_len = 454.343;
    vec_d         = vec2::normalize(vec_d, norm_len);
    auto vec_len  = vec2::length(vec_d);
    ASSERT_TRUE(c_m::relative_error(vec_len, rel_double_acc) == norm_len);

    auto vec_f = c_m::vector2f(-544, -24);
    norm_len   = 12.545;
    vec_f      = vec2::normalize(vec_f, norm_len);
    vec_len    = vec2::length(vec_f);

    ASSERT_TRUE(c_m::relative_error(vec_len, rel_double_acc) == norm_len);
}

TEST(vector2_operations, dot_product_test)
{
    auto vec1    = c_m::vector2d(32, 44);
    auto vec2    = c_m::vector2d(6, 3);
    auto product = vec2::dot_product(vec1, vec2);
    ASSERT_TRUE(c_m::relative_error(product, rel_double_acc) == 324.0);

    vec1    = c_m::vector2d(7, -8);
    vec2    = c_m::vector2d(-11, 23);
    product = vec2::dot_product(vec1, vec2);
    ASSERT_TRUE(c_m::relative_error(product, rel_float_acc) == -261.0);
}

TEST(vector2_operations, cos_angle_default_angle_test)
{
    auto vec1d   = c_m::vector2d(0.0, 1.0);
    auto vec2d   = c_m::vector2d(1.0, 0.0);
    auto cos_d   = vec2::cos_angle(vec1d, vec2d);
    auto angle_d = vec2::angle(vec1d, vec2d);
    ASSERT_TRUE(c_m::absolute_error(cos_d, abs_double_acc) == 0.0);
    ASSERT_TRUE(c_m::absolute_error(std::cos(angle_d), abs_double_acc) == cos_d);

    vec1d   = c_m::vector2d(-1.0, 0.0);
    vec2d   = c_m::vector2d(0.0, 1.0);
    cos_d   = vec2::cos_angle(vec1d, vec2d);
    angle_d = vec2::angle(vec1d, vec2d);
    ASSERT_TRUE(c_m::absolute_error(cos_d, abs_double_acc) == 0.0);
    ASSERT_TRUE(c_m::absolute_error(std::cos(angle_d), abs_double_acc) == cos_d);

    auto vec1f   = c_m::vector2f(1.0f, 0.0f);
    auto vec2f   = c_m::vector2f(3.0f, 4.0f);
    auto cos_f   = vec2::cos_angle(vec1f, vec2f);
    auto angle_f = vec2::angle(vec1f, vec2f);
    ASSERT_TRUE(c_m::relative_error(cos_f, rel_float_acc) == 0.6f);
    ASSERT_TRUE(c_m::relative_error(std::cos(angle_f), rel_float_acc) == cos_f);

    cos_f   = vec2::cos_angle(vec2f, vec1f);
    angle_f = vec2::angle(vec2f, vec1f);
    ASSERT_TRUE(c_m::relative_error(cos_f, rel_float_acc) == 0.6f);
    ASSERT_TRUE(c_m::relative_error(std::cos(angle_f), rel_float_acc) == cos_f);

    auto rotate_angle = c_m::pi / 2.0;
    vec1f             = p2::rotate(vec1f, rotate_angle);
    vec2f             = p2::rotate(vec2f, rotate_angle);
    cos_f             = vec2::cos_angle(vec1f, vec2f);
    angle_f           = vec2::angle(vec1f, vec2f);
    ASSERT_TRUE(c_m::relative_error(cos_f, rel_float_acc) == 0.6f);
    ASSERT_TRUE(c_m::relative_error(std::cos(angle_f), rel_float_acc) == cos_f);

    vec1f   = c_m::vector2f(1.0f, 0.0f);
    vec2f   = c_m::vector2f(-3.0f, 4.0f);
    cos_f   = vec2::cos_angle(vec1f, vec2f);
    angle_f = vec2::angle(vec1f, vec2f);
    ASSERT_TRUE(c_m::relative_error(cos_f, rel_float_acc) == -0.6f);
    ASSERT_TRUE(c_m::relative_error(std::cos(angle_f), rel_float_acc) == cos_f);

    vec1f   = c_m::vector2f(-5.0, 5.0);
    vec2f   = c_m::vector2f(-30.0, -30.0);
    cos_f   = vec2::cos_angle(vec1f, vec2f);
    angle_f = vec2::angle(vec1f, vec2f);
    ASSERT_TRUE(c_m::absolute_error(cos_f, abs_float_acc) == 0.0f);
    ASSERT_TRUE(c_m::absolute_error(std::cos(angle_f), abs_float_acc) == cos_f);

    vec1f   = c_m::vector2f(-32.0f, 11.23f);
    vec2f   = vec2::normalize(vec1f, 453.0);
    cos_f   = vec2::cos_angle(vec1f, vec2f);
    angle_f = vec2::angle(vec1f, vec2f);
    ASSERT_TRUE(c_m::relative_error(cos_f, rel_float_acc) == 1.0f);
    ASSERT_TRUE(c_m::relative_error(std::cos(angle_f), rel_float_acc) == cos_f);

    vec1f   = c_m::vector2f(-5.0, 2.3);
    vec2f   = c_m::vector2f(5.0, -2.3);
    cos_f   = vec2::cos_angle(vec1f, vec2f);
    angle_f = vec2::angle(vec1f, vec2f);
    ASSERT_TRUE(c_m::relative_error(cos_f, rel_float_acc) == -1.0f);
    ASSERT_TRUE(c_m::relative_error(std::cos(angle_f), rel_float_acc) == cos_f);
}

TEST(vector2_operations, pseudo_scalar_product_test)
{
    auto vec1     = c_m::vector2f(-10.0, 9.5);
    auto vec2     = c_m::vector2f(5.0, 0.0);
    auto prod     = vec2::pseudo_scalar_product(vec1, vec2);
    auto rev_prod = vec2::pseudo_scalar_product(vec2, vec1);
    ASSERT_TRUE(c_m::relative_error(prod, rel_float_acc) == -47.5);
    ASSERT_TRUE(c_m::relative_error(prod, rel_float_acc) == -rev_prod);

    vec1 = c_m::vector2f(-34.0, 21.0);
    vec2 = vec2::normalize(vec1, 5.0);
    prod = vec2::pseudo_scalar_product(vec1, vec2);
    ASSERT_TRUE(c_m::absolute_error(prod, abs_float_acc) == 0.0f);

    vec1 = c_m::vector2f(-20.0, 5.0);
    vec2 = c_m::vector2f(20.0, -5.0);
    vec2 = vec2::normalize(vec2, 9.5);
    prod = vec2::pseudo_scalar_product(vec1, vec2);
    ASSERT_TRUE(c_m::absolute_error(prod, abs_float_acc) == 0.0f);
}

TEST(vector2_operations, sign_angle_test)
{
    auto vec1      = c_m::vector2f(1.0, 0.0);
    auto vec2      = c_m::vector2f(4.0, 4.0);
    auto angle     = vec2::sign_angle(vec1, vec2);
    auto rev_angle = vec2::sign_angle(vec2, vec1);
    ASSERT_TRUE(c_m::relative_error(angle, rel_float_acc) == 45.0f / c_m::degree_per_radian);
    ASSERT_TRUE(c_m::relative_error(angle, rel_float_acc) == -rev_angle);

    vec1      = c_m::vector2f(-2.0, 6.0);
    vec2      = c_m::vector2f(6.0, 2.0);
    angle     = vec2::sign_angle(vec1, vec2);
    rev_angle = vec2::sign_angle(vec2, vec1);
    ASSERT_TRUE(c_m::relative_error(angle, rel_float_acc) == -90.0f / c_m::degree_per_radian);
    ASSERT_TRUE(c_m::relative_error(angle, rel_float_acc) == -rev_angle);

    vec1  = c_m::vector2f(6.0, 4.0);
    vec2  = c_m::vector2f(12.0, 8.0);
    angle = vec2::sign_angle(vec1, vec2);
    ASSERT_TRUE(c_m::absolute_error(angle, abs_float_acc) == 0.0);
}

TEST(vector2_operations, from_line_test)
{
    auto line = c_m::line2f(23.0, -12.5, 12.0, 15.6);
    auto vec  = vec2::from_line(line);
    ASSERT_TRUE(
        c_m::relative_error(vec.x, rel_float_acc) == -11.0
        && c_m::relative_error(vec.y, rel_float_acc) == 28.1
    );

    line = c_m::line2f(3.6, 3.2, 7.1, 1.1);
    vec  = vec2::from_line(line);
    ASSERT_TRUE(
        c_m::relative_error(vec.x, rel_float_acc) == 3.5
        && c_m::relative_error(vec.y, rel_float_acc) == -2.1
    );
}

TEST(vector2_operations, sin_cos_test)
{
    auto pythagorean_triple_list = std::vector<std::tuple<float, float, float>> {
        {  3.0f,   4.0f,   5.0f},
        { 20.0f,  21.0f,  29.0f},
        { 11.0f,  60.0f,  61.0f},
        { 39.0f,  80.0f,  89.0f},
        {115.0f, 252.0f, 277.0f}
    };

    for (auto& pyth_triple : pythagorean_triple_list)
    {
        auto x   = std::get<0>(pyth_triple);
        auto y   = std::get<1>(pyth_triple);
        auto len = std::get<2>(pyth_triple);

        auto vec     = c_m::vector2f(x, y);
        auto cos_val = vec2::cos(vec);
        auto sin_val = vec2::sin(vec);

        ASSERT_TRUE(
            c_m::relative_error(cos_val, rel_float_acc) == x / len
            && c_m::relative_error(sin_val, rel_float_acc) == y / len
        );
    }
}