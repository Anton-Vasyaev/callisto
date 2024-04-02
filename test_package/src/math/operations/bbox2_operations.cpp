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

using bbox2op = c_m::bbox2op;

constexpr double rel_double_acc = 1e-6;
constexpr double abs_double_acc = 1e-6;

constexpr float rel_float_acc = 1e-4;
constexpr float abs_float_acc = 1e-4;

TEST(bbox2_operations, normalize_reverse_normalize_test)
{
    auto p1  = c_m::point2f(1, -4);
    auto p2  = c_m::point2f(9, 12);
    auto box = c_m::bbox2f(p1, p2);

    auto contour = c_m::bbox2f(5, 4, 17, 14);
    box          = bbox2op::normalize(box, contour);

    ASSERT_TRUE(
        rel_err_bbox2_equal(box, c_m::bbox2f(-1.0 / 3.0, -0.8, 1.0 / 3.0, 0.8), rel_float_acc)
    );

    auto test_data_vec = std::vector<std::pair<c_m::bbox2f, c_m::bbox2f>> {
        {      { 0.12, 0.5, 0.6, 0.7 },     { -5.0, -6.0, 2.0, 4.5 }},
        {{ 23.55, 44.66, 23.86, 45.2 }, { 10.23, 12.56, 83.4, 76.2 }},
        {     { -0.5, -0.5, 0.5, 0.5 },       { 0.0, 0.0, 1.0, 1.0 }}
    };

    for (auto& test_data : test_data_vec)
    {
        auto norm_box         = c_m::bbox2op::normalize(test_data.first, test_data.second);
        auto reverse_norm_box = c_m::bbox2op::reverse_normalize(norm_box, test_data.second);

        ASSERT_TRUE(rel_err_bbox2_equal(reverse_norm_box, test_data.first, rel_float_acc));
    }
}

TEST(bbox2_operations, center_test)
{
    auto box           = c_m::bbox2f(-112.5, -11553.0, -100.1, -5023.4);
    auto expect_center = c_m::point2f(-106.3, -8288.2);

    auto center = c_m::bbox2op::center(box);
    ASSERT_TRUE(abs_err_point2_equal(center, expect_center, abs_float_acc));
}

TEST(bbox2_operations, scale_size_test)
{
    auto box = c_m::bbox2f(-23.5, 64.1, 1.2, 80.0);

    auto scale_size      = c_m::size2f(0.5, 1.6);
    auto expect_size_box = c_m::bbox2f(-17.325, 59.33, -4.975, 84.77);

    auto scale_box = c_m::bbox2op::scale(box, scale_size);

    ASSERT_TRUE(rel_err_bbox2_equal(scale_box, expect_size_box, rel_float_acc));

    auto scale_sizes = std::vector<c_m::size2f> {
        {0.5, 1.2},
        {3.0, 0.2},
        {4.5, 0.1},
        {5.2, 6.1}
    };

    scale_box = box;
    for (int i = 0; i < scale_sizes.size(); i++)
    {
        scale_box = c_m::bbox2op::scale(scale_box, scale_sizes[i]);
    }

    for (int i = scale_sizes.size() - 1; i >= 0; i--)
    {
        scale_box = c_m::bbox2op::scale(scale_box, c_m::size2f(1.0, 1.0) / scale_sizes[i]);
    }

    ASSERT_TRUE(rel_err_bbox2_equal(box, scale_box, rel_float_acc));
}

TEST(bbox2_operations, move_test)
{
    auto box         = c_m::bbox2f(-23.5, 64.1, 1.2, 80.0);
    auto move_vector = c_m::vector2f(11.5, 23.4);
    auto expect_box  = c_m::bbox2f(-12.0, 87.5, 12.7, 103.4);

    auto move_box = c_m::bbox2op::move(box, move_vector);
    ASSERT_TRUE(rel_err_bbox2_equal(move_box, expect_box, rel_float_acc));

    auto move_vectors = std::vector<c_m::vector2f> {
        { 12.4, 56.2},
        {  0.5, 0.34},
        {-18.2, 16.1},
        {  9.2, -4.5},
        { 10.0, 10.0},
        {  1.0,  2.0},
        {  2.0,  3.0}
    };

    move_box = box;
    for (int i = 0; i < move_vectors.size(); i++)
    {
        move_box = c_m::bbox2op::move(move_box, move_vectors[i]);
    }

    for (int i = move_vectors.size() - 1; i >= 0; i--)
    {
        move_box = c_m::bbox2op::move(move_box, -move_vectors[i]);
    }

    ASSERT_TRUE(rel_err_bbox2_equal(move_box, box, rel_float_acc));
}

TEST(bbox2_operations, from_center_test)
{
    auto test_data_vec = std::vector<c_m::bbox2f> {
        { 0.12,   0.5,   0.6,  0.7},
        { -5.0,  -6.0,   2.0,  4.5},
        {23.55, 44.66, 23.86, 45.2},
        {10.23, 12.56,  83.4, 76.2},
        { -0.5,  -0.5,   0.5,  0.5},
    };

    for (auto& test_box : test_data_vec)
    {
        auto w = test_box.width();
        auto h = test_box.height();

        auto x_c = test_box.x1 + w / 2.0f;
        auto y_c = test_box.y1 + h / 2.0f;

        auto center = c_m::point2f(x_c, y_c);
        auto size   = c_m::size2d(w, h);

        auto box = c_m::bbox2op::from_center(center.as<float>(), size.as<float>());

        ASSERT_TRUE(rel_err_bbox2_equal(box, test_box, rel_float_acc));
    }
}