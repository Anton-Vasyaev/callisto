// parent header
#include <callisto/graphics/freetype/bindings/bitmap_auxiliary.hpp>
// 3rd party
#include <nameof.hpp>
// project
#include <callisto/framework/exception.hpp>
#include <callisto/framework/string.hpp>

#include <callisto/graphics/freetype/enum/pixel_mode.hpp>

namespace c_f  = callisto::framework;
namespace c_cv = callisto::opencv;

namespace callisto::graphics::freetype
{

cv::Mat bitmap_auxiliary::get_mat_present(FT_Bitmap bitmap)
{
    if (bitmap.pitch <= 0)
    {
        throw c_f::runtime_exception() << c_f::error_tag_message(c_f::_bs(
            "Failed to execute ",
            NAMEOF(bitmap_auxiliary::get_mat_present),
            ". Pitch <= 0: ",
            bitmap.pitch
        ));
    }

    auto data_ptr = (uint8_t*)bitmap.buffer;

    c_cv::image_type img_type;
    size_t           height, width, stride;
    if (bitmap.pixel_mode == FT_Pixel_Mode::FT_PIXEL_MODE_GRAY)
    {
        img_type = c_cv::image_type::grayscale;
        width    = bitmap.width;
        height   = bitmap.rows;
    }
    else if (bitmap.pixel_mode == FT_Pixel_Mode::FT_PIXEL_MODE_LCD)
    {
        img_type = c_cv::image_type::bgr;
        width    = bitmap.width / 3;
        height   = bitmap.rows;
    }
    else
    {
        throw c_f::runtime_exception() << c_f::error_tag_message(
            c_f::_bs("Invalid pixel mode of bitmap:", pixel_mode_str(bitmap.pixel_mode))
        );
    }
    stride = bitmap.pitch;

    auto mat_type = c_cv::make_type(c_f::numeric_type::uint8(), img_type);

    auto present_mat = cv::Mat(height, width, mat_type, data_ptr, stride);

    return present_mat;
}

} // namespace callisto::graphics::freetype