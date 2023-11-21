// parent header
#include <callisto/opencv/auxiliary.hpp>
// 3rd party
#include <callisto/framework/exception.hpp>

namespace callisto::opencv
{

void match_image_type(const cv::Mat& mat, image_type img_type, const char* function_name)
{
    auto mat_channels      = type_channels(mat.type());
    auto img_type_channels = image_type_channels(img_type);

    auto func_name = function_name != nullptr ? function_name : "unknown location";

    if (mat_channels != img_type_channels)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(c_f::_bs(
            "img type channels != mat channels:",
            img_type_channels,
            " != ",
            mat_channels,
            ". Vallidate call from \'",
            func_name,
            "\'"
        ));
    }
}

image_type default_image_type(const cv::Mat& mat)
{
    auto channels = mat.channels();

    switch (channels)
    {
        case 1 : return image_type::grayscale;
        case 3 : return image_type::bgr;
        case 4 : return image_type::bgra;

        default :
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(
                c_f::_bs("not exist default image_type for cv::Mat channels:", channels)
            );
    }
}

} // namespace callisto::opencv