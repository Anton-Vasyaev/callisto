#pragma once

#include <opencv2/opencv.hpp>
#include <callisto/math/primitives/rectangle.hpp>
#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/math/primitives/bbox2.hpp>
#include "auxiliary.hpp"

namespace callisto::opencv
{

void resize_frame(
    cv::InputArray  src,
    cv::OutputArray dst,
    cv::Size        dsize,
    int             interpolation = cv::INTER_AREA
);

cv::Mat roi(cv::Mat& img, callisto::math::rectangle_i rect)
{
    auto x = rect.x;
    auto y = rect.y;
    auto w = rect.width;
    auto h = rect.height;

    return img({ x, y, w, h });
}

template<typename rectangle_type>
cv::Mat norm_roi(cv::Mat& img, callisto::math::rectangle<rectangle_type> rect)
{
    auto size = mat_size(img);

    rect.position *= size;
    rect.size *= size;

    return roi(img, rect.as<int32_t>());
}

template<typename lt_type, typename rb_type>
cv::Mat roi(cv::Mat& img, callisto::math::point2i left_top, callisto::math::point2i right_bottom)
{
    auto l = left_top.x;
    auto t = left_top.y;

    auto r = right_bottom.x;
    auto b = right_bottom.y;

    return img({ t, b }, { l, r });
}

template<typename lt_type, typename rb_type>
cv::Mat norm_roi(
    cv::Mat&                            img,
    callisto::math::alg_tuple2<lt_type> left_top,
    callisto::math::alg_tuple2<rb_type> right_bottom
)
{
    auto size = mat_size(img);

    left_top *= size;
    right_bottom *= size;

    return roi(img, left_top.as<int32_t>(), right_bottom.as<int32_t>());
}

template<typename box_type>
cv::Mat roi(cv::Mat& img, callisto::math::bbox2i box)
{
    return roi(img, box.left_top(), box.right_bottom());
}

template<typename box_type>
cv::Mat norm_roi(cv::Mat& img, callisto::math::bbox2<box_type> box)
{
    return norm_roi(img, box.left_top(), box.right_bottom());
}

} // namespace callisto::opencv