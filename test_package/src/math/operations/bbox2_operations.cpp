// test
#include <callisto/math/operations/bbox2op.hpp>
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

TEST(bbox2_operations, normalize_test)
{
    auto p1  = c_m::point2f(1, -4);
    auto p2  = c_m::point2f(9, 12);
    auto box = c_m::bbox2f(p1, p2);

    auto contour = c_m::bbox2f(5, 4, 17, 14);
    box          = bbox2op::normalize(box, contour);

    std::cout << "line:" << line << "\n";

    ASSERT_TRUE(
        rel_err_bbox2_equal(line, c_m::line2f(1.0 / 3.0, 0.8, -1.0 / 3.0, -0.8), rel_float_acc)
    );
}