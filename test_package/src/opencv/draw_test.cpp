// test
#include <callisto/opencv/draw.hpp>
// std
#include <iostream>
#include <ranges>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/opencv/auxiliary.hpp>
#include <callisto/opencv/rw.hpp>

namespace c_f  = callisto::framework;
namespace c_m  = callisto::math;
namespace c_cv = callisto::opencv;

TEST(opencv_auxiliary, draw_test_placeholder)
{
    auto      img_type = c_cv::make_type(c_f::numeric_type::uint8, c_cv::image_type::bgr);
    const int img_w    = 1500;
    const int img_h    = 1500;

    cv::Mat mat = cv::Mat::zeros(img_h, img_w, img_type);

    c_cv::draw_bbox_p(mat, { 0.2, 0.2 }, { 0.4, 0.4 }, { 255, 128, 64 }, 2);

    c_cv::draw_bbox(mat, { 0.3, 0.3, 0.35, 0.35 }, { 200, 170, 130 }, 2);

    c_cv::draw_line_p(mat, { 0.4, 0.2 }, { 0.6, 0.2 }, { 64, 128, 32 }, 2);

    c_cv::draw_line(mat, { 0.4, 0.8, 0.6, 0.8 }, { 64, 128, 32 }, 2);

    auto poly = std::vector<c_m::point2f> {
        { 0.5,  0.5},
        { 0.6,  0.7},
        { 0.9,  0.9},
        {0.55, 0.77},
        {0.45, 0.66}
    };

    c_cv::fill_polygon(mat, poly, { 255, 0, 0 });

    c_cv::draw_polygon(mat, poly, { 0, 255, 0 }, 4);

    auto curve_line = std::vector<c_m::point2f> {
        {0.75, 0.25},
        { 0.8, 0.35},
        {0.95,  0.4},
        {0.75,  0.7}
    };

    c_cv::draw_polyline(mat, curve_line, { 0, 0, 255 }, 3);

    c_cv::draw_circle(mat, { 0.25, 0.75 }, { 64, 95, 180 }, 5);

    c_cv::imwrite("opencv_draw_output.png", mat);
}
