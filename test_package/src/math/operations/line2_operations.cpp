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
    ASSERT_TRUE(rel_err_point2_equal(cross_p.as<float>(), c_m::point2f(6.0, 2.0), rel_float_acc));

    line1   = c_m::line2f(5.0, 5.0, 2.0, 2.0);
    line2   = c_m::line2f(3.0, 1.0, 1.0, 3.0);
    cross_p = line2op::cross_point(line1, line2);
    ASSERT_TRUE(rel_err_point2_equal(cross_p.as<float>(), c_m::point2f(2.0, 2.0), rel_float_acc));

    line1   = c_m::line2f(5.0, 5.0, -10.0, -10.0);
    line2   = c_m::line2f(16.0, 32.0, 4.0, 8.0);
    cross_p = line2op::cross_point(line1, line2);
    ASSERT_TRUE(abs_err_point2_equal(cross_p.as<float>(), c_m::point2f::empty(), abs_float_acc));
}

TEST(line2_operations, get_box_contour_test)
{
    auto line = c_m::line2f(15.0F, 23.0F, 43.5F, 36.2F);
    auto box  = line2op::get_box_contour(line);
    ASSERT_TRUE(rel_err_bbox2_equal(box, c_m::bbox2f(15.0F, 23.0F, 43.5F, 36.2F), rel_float_acc));

    line = c_m::line2f(-23.0, 34.5, -34.5, 23.21);
    box  = line2op::get_box_contour(line);
    ASSERT_TRUE(rel_err_bbox2_equal(box, c_m::bbox2f(-34.5F, 23.21F, -23.0F, 34.5F), rel_float_acc)
    );
}

TEST(line2_operations, normalize_test)
{
    auto p1   = c_m::point2f(9, 12);
    auto p2   = c_m::point2f(1, -4);
    auto line = c_m::line2f(p1, p2);

    auto box = c_m::bbox2f(5, 4, 17, 14);
    line     = line2op::normalize(line, box);

    ASSERT_TRUE(rel_err_line2_equal(
        line,
        c_m::line2f(1.0F / 3.0F, 0.8F, -1.0F / 3.0F, -0.8F),
        rel_float_acc
    ));
}