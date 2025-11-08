// test
#include <callisto/math/operations/vector3op.hpp>

// std
#include <array>

// 3rd party
#include <gtest/gtest.h>

// project
#include <callisto/framework/test/gtest.hpp>
#include <callisto/math/primitives.hpp>
#include <callisto/math/error.hpp>
#include <callisto/math/operations/point3op.hpp>
#include <callisto/math/constants.hpp>

#include <math/auxiliary/print_math_data.hpp>
#include <math/auxiliary/data_equal.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

template<typename numeric_type>
using err = c_m::relative_error<numeric_type>;

using out = c_f::gtest_console;

constexpr double REL_DOUBLE_ACC = 1e-6;
constexpr double ABS_DOUBLE_ACC = 1e-6;

constexpr float REL_FLOAT_ACC = 1e-4;
constexpr float ABS_FLOAT_ACC = 1e-4;

auto NUMBER_SIGNS = std::array<float, 2> { -1.0, 1.0 };

TEST(vector3_operations, square_of_length_test)
{
    auto vec        = c_m::vector3d(5, 6, 7);
    auto expect_val = 110;

    for (auto first_sign : NUMBER_SIGNS)
    {
        for (auto second_sign : NUMBER_SIGNS)
        {
            for (auto third_sign : NUMBER_SIGNS)
            {
                auto x = vec.x * first_sign;
                auto y = vec.y * second_sign;
                auto z = vec.z * third_sign;

                auto curr_vec = c_m::vector3d(x, y, z);
                auto sq_len   = c_m::vector3op::square_of_length(curr_vec);

                ASSERT_TRUE(c_m::relative_error(sq_len, REL_DOUBLE_ACC) == expect_val);
            }
        }
    }
}

TEST(vector3_operations, length_test)
{
    auto vec        = c_m::vector3d(12.0, 16.0, 21.0);
    auto expect_val = 29.0;

    for (auto first_sign : NUMBER_SIGNS)
    {
        for (auto second_sign : NUMBER_SIGNS)
        {
            for (auto third_sign : NUMBER_SIGNS)
            {
                auto x = vec.x * first_sign;
                auto y = vec.y * second_sign;
                auto z = vec.z * third_sign;

                auto curr_vec = c_m::vector3d(x, y, z);
                auto sq_len   = c_m::vector3op::length(curr_vec);

                ASSERT_TRUE(c_m::relative_error(sq_len, REL_DOUBLE_ACC) == expect_val);
            }
        }
    }
}

TEST(vector3_operations, normalize_test)
{
    auto vectors = std::vector<c_m::vector3f> {
        {   0.5,    0.4,   0.3},
        {   0.0,    0.3,   0.0},
        { -0.21,   0.77,  0.23},
        {   1.0,    1.0,   1.0},
        { -23.0,   56.2, -23.5},
        {-112.3, -544.0,  66.5},
        {  23.5,   76.6, -21.2}
    };

    auto normalize_values = std::vector<float> { 1.0, 10.0, 0.5, 23.0, 111.11 };

    for (auto& vec : vectors)
    {
        for (auto norm_val : normalize_values)
        {
            auto norm_vec = c_m::vector3op::normalize(vec, norm_val);
            auto norm_len = c_m::vector3op::length(norm_vec);
            ASSERT_TRUE(c_m::relative_error(norm_len, REL_FLOAT_ACC) == norm_val);
        }
    }
}

TEST(vector3_operations, cross_product_test)
{
    struct test_example
    {
        c_m::vector3f first_vec;
        c_m::vector3f second_vec;
        c_m::vector3f result_vec;
    };

    auto test_pairs = std::vector<test_example> {
        {      { 2.0, 3.0, 4.0 },       { 5.0, 6.0, 7.0 }, { -3.0, 6.0, -3.0 }},
        {{ -10.0, -11.0, -12.0 }, { -13.0, -14.0, -15.0 }, { -3.0, 6.0, -3.0 }},
        {      { 1.0, 0.0, 0.0 },       { 0.0, 1.0, 0.0 },   { 0.0, 0.0, 1.0 }}
    };

    for (auto& test_example : test_pairs)
    {
        auto cross_vec
            = c_m::vector3op::cross_product(test_example.first_vec, test_example.second_vec);
        ASSERT_TRUE(abs_err_point3_equal(test_example.result_vec, cross_vec, ABS_FLOAT_ACC));
    }
}