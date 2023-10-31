// test
#include <callisto/math/operations/poly2op.hpp>
// 3rd party
#include <gtest/gtest.h>

// project
#include <callisto/framework/test/gtest.hpp>
#include <callisto/math/primitives.hpp>
#include <callisto/math/constants.hpp>

#include <math/auxiliary/print_math_data.hpp>
#include <math/auxiliary/data_equal.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

using poly2op = c_m::poly2op;

constexpr double rel_double_acc = 1e-6;
constexpr double abs_double_acc = 1e-6;

constexpr float rel_float_acc = 1e-4;
constexpr float abs_float_acc = 1e-4;

TEST(poly2_operations, area_test)
{
    struct test_data
    {
        std::vector<c_m::point2f> polygon;

        float area;

        std::vector<c_m::point2f> contain_point_list;

        std::vector<c_m::point2f> not_contain_point_list;
    };

    // clang-format off
    auto test_data_list = std::vector<test_data> {
        {
            {
                c_m::point2f(1.0, 1.0),
                c_m::point2f(3.0, 5.0),
                c_m::point2f(4.0, 3.0),
                c_m::point2f(3.0, 2.0),
                c_m::point2f(4.0, 1.0),
                c_m::point2f(5.0, 2.0),
                c_m::point2f(5.0, 6.0),
                c_m::point2f(3.0, 8.0),
                c_m::point2f(1.0, 5.0) 
            },
            16.5,
            { 
                c_m::point2f(2.0, 4.0),
                c_m::point2f(3.0, 6.0),
                c_m::point2f(4.0, 6.0),
                c_m::point2f(4.0, 5.0),
                c_m::point2f(4.5, 3.0),
                c_m::point2f(4.0, 2.0) 
            },
            { 
                c_m::point2f(0.0, 0.0),
                c_m::point2f(2.0, 2.0),
                c_m::point2f(3.0, 4.0),
                c_m::point2f(3.5, 3.0),
                c_m::point2f(2.0, 7.0),
                c_m::point2f(3.0, 1.0),
                c_m::point2f(4.0, 8.0)
            }
        }
    };
    // clang-format on

    for (auto& test_data : test_data_list)
    {
        auto calc_area = poly2op::area(test_data.polygon);

        ASSERT_TRUE(c_m::relative_error(calc_area, rel_float_acc) == test_data.area);

        for (auto& contain_point : test_data.contain_point_list)
        {
            ASSERT_TRUE(poly2op::contain(test_data.polygon, contain_point));
        }

        for (auto& not_contain_point : test_data.not_contain_point_list)
        {
            ASSERT_FALSE(poly2op::contain(test_data.polygon, not_contain_point));
        }
    }
}