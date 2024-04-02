// test
#include <callisto/math/operations/point3op.hpp>
// std
#include <functional>
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

constexpr double rel_double_acc = 1e-6;
constexpr double abs_double_acc = 1e-6;

constexpr float rel_float_acc = 1e-4;
constexpr float abs_float_acc = 1e-4;

TEST(point3_operations, get_box3_contour_test)
{
    auto points = std::vector<c_m::point3f> {
        {   0.0,   2.0,   3.0},
        {   0.3,   0.6,   0.0},
        { -11.2,  34.5, -23.0},
        {-21.23, 44.56,   4.5},
        {  97.5,  61.2,  44.3},
        {  10.0,  10.0,   0.0},
        { -11.3,  -5.3,  11.2},
        {   0.0,   0.0, -5.67},
        {  21.5,  34.6,  44.4}
    };

    auto expected_box = c_m::bbox3f { -21.23, -5.3, -23.0, 97.5, 61.2, 44.4 };

    auto contour_box = c_m::point3op::get_box_contour(std::span(points));

    ASSERT_TRUE(rel_err_bbox3_equal(contour_box, expected_box, rel_float_acc));
}
