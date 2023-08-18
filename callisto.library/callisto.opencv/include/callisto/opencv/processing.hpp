#pragma once

#include <opencv2/opencv.hpp>
#include <callisto/math/primitives/rectangle.hpp>
#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/math/primitives/bbox2.hpp>
#include "auxiliary.hpp"

namespace callisto::opencv
{

namespace
{
namespace c_m = callisto::math;
}

void resize_frame(
    cv::InputArray  src,
    cv::OutputArray dst,
    cv::Size        dsize,
    int             interpolation = cv::INTER_AREA
);

template<typename rectangle_type>
cv::Mat roi(cv::Mat& img, c_m::rectangle<rectangle_type> rect)
{
    auto x = (int)rect.position.x;
    auto y = (int)rect.position.y;
    auto w = (int)rect.size.width;
    auto h = (int)rect.size.height;

    return img({ x, y, w, h });
}

template<typename rectangle_type>
cv::Mat norm_roi(cv::Mat& img, c_m::rectangle<rectangle_type> rect)
{
    auto size = mat_size(img);

    rect.position *= size;
    rect.size *= size;

    return roi(img, rect);
}

template<typename lt_type, typename rb_type>
cv::Mat roi(cv::Mat& img, c_m::alg_tuple2<lt_type> left_top, c_m::alg_tuple2<rb_type> right_bottom)
{
    auto l = (int)left_top.x;
    auto t = (int)left_top.y;

    auto r = (int)right_bottom.x;
    auto b = (int)right_bottom.y;

    return img({ t, b }, { l, r });
}

template<typename lt_type, typename rb_type>
cv::Mat
norm_roi(cv::Mat& img, c_m::alg_tuple2<lt_type> left_top, c_m::alg_tuple2<rb_type> right_bottom)
{
    auto size = mat_size(img);

    left_top *= size;
    right_bottom *= size;

    return roi(img, left_top, right_bottom);
}

template<typename box_type>
cv::Mat roi(cv::Mat& img, c_m::bbox2<box_type> box)
{
    return roi(img, box.left_top(), box.right_bottom());
}

template<typename box_type>
cv::Mat norm_roi(cv::Mat& img, c_m::bbox2<box_type> box)
{
    return norm_roi(img, box.left_top(), box.right_bottom());
}

} // namespace callisto::opencv