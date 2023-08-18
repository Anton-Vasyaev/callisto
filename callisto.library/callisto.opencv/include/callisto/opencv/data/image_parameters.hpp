#pragma once

// std
#include <utility>
// 3rd party
#include <callisto/framework/native/numeric_type.hpp>
// project
#include "image_type.hpp"
#include <callisto/opencv/auxiliary.hpp>

namespace callisto::opencv
{

namespace
{
namespace c_f = callisto::framework;
}

struct image_parameters
{
    c_f::numeric_type num_type;

    image_type img_type;

    size_t width;

    size_t height;

    size_t stride;

    inline static image_parameters from_mat(cv::Mat mat, image_type img_type = image_type::unknown)
    {
        auto mat_type = mat.type();

        auto numeric_type = cv2numeric(mat_type);
        auto channels     = type_channels(mat_type);

        auto selected_img_type
            = img_type == image_type::unknown ? default_image_type(mat) : img_type;

        return image_parameters { numeric_type,
                                  img_type,
                                  (size_t)mat.cols,
                                  (size_t)mat.rows,
                                  (size_t)mat.step };
    }
};

} // namespace callisto::opencv