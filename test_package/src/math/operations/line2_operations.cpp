// test
#include <callisto/math/operations/line2op.hpp>
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

using line2op = c_m::line2op;

constexpr double rel_double_acc = 1e-6;
constexpr double abs_double_acc = 1e-6;

constexpr float rel_float_acc = 1e-4;
constexpr float abs_float_acc = 1e-4;

TEST(line2_operations, cross_point_test)
{
    auto line1   = c_m::line2f(4.0, -2.0, 7.0, 4.0);
    auto line2   = c_m::line2f(3.0, 3.0, -3.0, 5.0);
    auto cross_p = line2op::cross_point(line1, line2);
    ASSERT_TRUE(rel_err_point2_equal(cross_p, c_m::point2f(6.0, 2.0), rel_float_acc));

    line1   = c_m::line2f(5.0, 5.0, 2.0, 2.0);
    line2   = c_m::line2f(3.0, 1.0, 1.0, 3.0);
    cross_p = line2op::cross_point(line1, line2);
    ASSERT_TRUE(rel_err_point2_equal(cross_p, c_m::point2f(2.0, 2.0), rel_float_acc));

    line1   = c_m::line2f(5.0, 5.0, -10.0, -10.0);
    line2   = c_m::line2f(16.0, 32.0, 4.0, 8.0);
    cross_p = line2op::cross_point(line1, line2);
    ASSERT_TRUE(abs_err_point2_equal(cross_p, c_m::point2f::empty(), abs_float_acc));
}

TEST(line2_operations, get_bbox_test)
{
    auto line = c_m::line2f(15.0f, 23.0f, 43.5f, 36.2f);
    auto box  = line2op::get_bbox(line);
    ASSERT_TRUE(rel_err_bbox2_equal(box, c_m::bbox2f(15.0f, 23.0f, 43.5, 36.2f), rel_float_acc));

    line = c_m::line2f(-23.0, 34.5, -34.5, 23.21);
    box  = line2op::get_bbox(line);
    ASSERT_TRUE(rel_err_bbox2_equal(box, c_m::bbox2f(-34.5, 23.21, -23.0, 34.5), rel_float_acc));
}
