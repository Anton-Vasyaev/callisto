// parent header
#include <callisto/opencv/processing.hpp>

namespace callisto::opencv
{

void resize_frame(cv::InputArray src, cv::OutputArray dst, const cv::Size& dsize, int interpolation)
{
    auto im_h = static_cast<float>(src.rows());
    auto im_w = static_cast<float>(src.cols());

    auto w_scale = static_cast<float>(dsize.width) / im_w;
    auto h_scale = static_cast<float>(dsize.height) / im_h;

    auto scale = (std::min)(w_scale, h_scale);

    auto new_w = static_cast<int>(im_w * scale);
    auto new_h = static_cast<int>(im_h * scale);

    cv::resize(src, dst, { new_w, new_h }, 0.0, 0.0, interpolation);
}

} // namespace callisto::opencv