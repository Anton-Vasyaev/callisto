#pragma once

// parent header
#include <callisto/opencv/processing.hpp>

namespace callisto::opencv
{

void resize_frame(cv::InputArray src, cv::OutputArray dst, cv::Size dsize, int interpolation)
{
    auto im_h = src.rows();
    auto im_w = src.cols();

    auto w_scale = float(dsize.width) / im_w;
    auto h_scale = float(dsize.height) / im_h;

    auto scale = std::min(w_scale, h_scale);

    auto new_w = int(im_w * scale);
    auto new_h = int(im_h * scale);

    cv::resize(src, dst, { new_w, new_h }, 0.0f, 0.0f, interpolation);
}

} // namespace callisto::opencv