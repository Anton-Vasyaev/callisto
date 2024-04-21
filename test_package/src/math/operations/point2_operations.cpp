// test
#include <callisto/math/operations/point2op.hpp>
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

using p2op = c_m::point2op;

constexpr double rel_double_acc = 1e-6;
constexpr double abs_double_acc = 1e-6;

constexpr float rel_float_acc = 1e-4;
constexpr float abs_float_acc = 1e-4;

TEST(point2_operations, square_distance_default_distance_test)
{
    struct square_distance_test_data
    {
        c_m::point2f first_point;
        c_m::point2f second_point;

        float expect;
    };

    auto data_list = std::vector<square_distance_test_data> {
        { { 11.2, 15.3 }, { -74.3, 12.2 }, 7319.86},
        {{ -23.6, 53.7 }, { -10.0, -7.4 }, 3918.17},
        { { -5.0, -6.0 },  { -7.0, -8.0 },     8.0},
        {  { 4.3, -3.2 },  { 5.7, -21.5 },  336.85}
    };

    for (auto& data : data_list)
    {
        auto p1     = data.first_point;
        auto p2     = data.second_point;
        auto expect = data.expect;

        auto square_len1 = p2op::square_distance(p1, p2);
        auto square_len2 = p2op::square_distance(p1, p2);

        ASSERT_TRUE(c_m::relative_error(square_len1, rel_float_acc) == expect);
        ASSERT_TRUE(c_m::relative_error(square_len1, rel_float_acc) == square_len2);

        auto len1 = p2op::distance(p1, p2);
        auto len2 = p2op::distance(p2, p1);

        ASSERT_TRUE(c_m::relative_error(len1, rel_float_acc) == std::sqrt(square_len1));
        ASSERT_TRUE(c_m::relative_error(len1, rel_float_acc) == len2);
    }
}

TEST(point2_operations, rotate_default_rotate_anchor_test)

{
    struct rotate_operation_data
    {
        float x;

        float y;

        float len;

        c_m::point2f offset_point;
    };

    auto test_data_list = std::vector<rotate_operation_data> {
        {  3.0f,   4.0f,   5.0f,  { -23.5, 43.2f }},
        { 20.0f,  21.0f,  29.0f,  { 17.63, 10.0f }},
        { 11.0f,  60.0f,  61.0f,  { 18.21, 74.2f }},
        { 39.0f,  80.0f,  89.0f, { -45.15, 51.9f }},
        {115.0f, 252.0f, 277.0f,  { 67.25, 73.2f }}
    };

    for (auto& data : test_data_list)
    {
        auto x            = data.x;
        auto y            = data.y;
        auto len          = data.len;
        auto offset_point = data.offset_point;

        auto cos_val             = x / len;
        auto first_rotate_angle  = std::acos(cos_val);
        auto second_rotate_angle = (c_m::deg2rad(90.0) - first_rotate_angle) * 2.0;

        auto start_point = c_m::point2f(len, 0.0);

        // positive rotate angle
        auto first_rotate_point = p2op::rotate(start_point, first_rotate_angle).as<float>();
        auto second_rotate_point
            = p2op::rotate(first_rotate_point, second_rotate_angle).as<float>();
        ASSERT_TRUE(rel_err_point2_equal(first_rotate_point, c_m::point2f(x, y), rel_float_acc));
        ASSERT_TRUE(rel_err_point2_equal(second_rotate_point, c_m::point2f(-x, y), rel_float_acc));

        // negative rotate angle
        first_rotate_point  = p2op::rotate(start_point, -first_rotate_angle).as<float>();
        second_rotate_point = p2op::rotate(first_rotate_point, -second_rotate_angle).as<float>();
        ASSERT_TRUE(rel_err_point2_equal(first_rotate_point, c_m::point2f(x, -y), rel_float_acc));
        ASSERT_TRUE(rel_err_point2_equal(second_rotate_point, c_m::point2f(-x, -y), rel_float_acc));

        start_point += offset_point;

        // positive rotate angle with offset
        first_rotate_point
            = p2op::rotate_anchor(start_point, first_rotate_angle, offset_point).as<float>();
        second_rotate_point
            = p2op::rotate_anchor(first_rotate_point, second_rotate_angle, offset_point)
                  .as<float>();
        ASSERT_TRUE(rel_err_point2_equal(
            first_rotate_point - offset_point,
            c_m::point2f(x, y),
            rel_float_acc
        ));
        ASSERT_TRUE(rel_err_point2_equal(
            second_rotate_point - offset_point,
            c_m::point2f(-x, y),
            rel_float_acc
        ));

        // negative rotate angle with offset
        first_rotate_point
            = p2op::rotate_anchor(start_point, -first_rotate_angle, offset_point).as<float>();
        second_rotate_point
            = p2op::rotate_anchor(first_rotate_point, -second_rotate_angle, offset_point)
                  .as<float>();
        ASSERT_TRUE(rel_err_point2_equal(
            first_rotate_point - offset_point,
            c_m::point2f(x, -y),
            rel_float_acc
        ));
        ASSERT_TRUE(rel_err_point2_equal(
            second_rotate_point - offset_point,
            c_m::point2f(-x, -y),
            rel_float_acc
        ));
    }
}

TEST(point2_operations, clamp_test)
{
    auto p       = c_m::point2f(-23, 40);
    auto box     = c_m::bbox2f(1, 2, 3, 4);
    auto clamp_p = p2op::clamp(p, box);
    ASSERT_TRUE(rel_err_point2_equal(clamp_p, c_m::point2f(1.0, 4.0), rel_float_acc));

    p       = c_m::point2f(256.23, -443.5);
    box     = c_m::bbox2f(-5.0, -3.2, -6.0, 23.0);
    clamp_p = p2op::clamp(p, box);
    ASSERT_TRUE(rel_err_point2_equal(clamp_p, c_m::point2f(-6.0, -3.2), rel_float_acc));

    p       = c_m::point2f(12.5, 21.333);
    box     = c_m::bbox2f(4.7, 10.11, 17.23, 37.56);
    clamp_p = p2op::clamp(p, box);
    ASSERT_TRUE(rel_err_point2_equal(clamp_p, c_m::point2f(12.5, 21.333), rel_float_acc));
}

TEST(point2_operations, normalize_reverse_normalize_test)
{
    using namespace std::placeholders;

    auto p   = c_m::point2f(9, 12);
    auto box = c_m::bbox2f(5, 4, 17, 14);
    p        = p2op::normalize(p, box);
    ASSERT_TRUE(rel_err_point2_equal(p, c_m::point2f(1.0 / 3.0, 0.8), rel_float_acc));

    p = c_m::point2f(-1, -4);
    p = p2op::normalize(p, box);
    ASSERT_TRUE(rel_err_point2_equal(p, c_m::point2f(-0.5, -0.8), rel_float_acc));

    auto test_points = std::vector<c_m::point2f> {
        {   11.2,   0.64},
        { -0.345,   0.02},
        {-0.0023, -0.055},
        {  -20.3,   44.5},
        {    5.3,    7.5},
        {    0.0,    0.0}
    };

    auto test_boxes = std::vector<c_m::bbox2f> {
        {  0.0,   0.0,  1.0,   1.0},
        { -5.0,  -3.4, 23.6,  11.2},
        { 44.5,  43.2, 71.2,  51.2},
        {-11.0, -14.0, -9.0, -12.0}
    };

    for (auto test_point : test_points)
    {
        for (auto test_box : test_boxes)
        {
            auto norm_point = c_m::point2op::normalize(test_point, test_box);
            auto rev_point  = c_m::point2op::reverse_normalize(norm_point, test_box);

            std::function<bool(c_m::point2f, c_m::point2f)> accuracy_func;

            if (test_point == c_m::point2f(0.0, 0.0))
            {
                accuracy_func = std::bind(abs_err_point2_equal<float>, _1, _2, abs_float_acc);
            }
            else
            {
                accuracy_func = std::bind(rel_err_point2_equal<float>, _1, _2, 1e-3);
            }

            ASSERT_TRUE(accuracy_func(test_point, rev_point));
        }
    }
}

TEST(point2_operations, get_box_contour_test)
{
    auto points = std::vector<c_m::point2f> {
        {   0.0,   2.0},
        {   0.3,   0.6},
        { -11.2,  34.5},
        {-21.23, 44.56},
        {  97.5,  61.2},
        {  10.0,  10.0},
        { -11.3,  -5.3},
        {   0.0,   0.0},
        {  21.5,  34.6}
    };

    auto expected_box = c_m::bbox2f { -21.23, -5.3, 97.5, 61.2 };

    auto contour_box = c_m::point2op::get_box_contour(std::span(points));

    ASSERT_TRUE(rel_err_bbox2_equal(contour_box, expected_box, rel_float_acc));
}