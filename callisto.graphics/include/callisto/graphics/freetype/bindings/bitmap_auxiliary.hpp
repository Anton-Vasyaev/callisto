#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// project
#include <callisto/opencv.hpp>

namespace callisto::graphics::freetype
{
struct bitmap_auxiliary
{
    static cv::Mat get_mat_present(FT_Bitmap bitmap);
};
} // namespace callisto::graphics::freetype