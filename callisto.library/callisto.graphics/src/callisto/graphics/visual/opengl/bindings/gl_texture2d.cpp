// parent header
#include <callisto/graphics/visual/opengl/bindings/gl_texture2d.hpp>
// 3rd party
#include <callisto/opencv/auxiliary.hpp>

namespace callisto::graphics
{

void gl_texture2d::__initialize_data(const cv::Mat& img, callisto::opencv::image_type img_type)
{
    namespace c_f  = callisto::framework;
    namespace c_cv = callisto::opencv;
    if (img_type == c_cv::image_type::unknown)
    {
        img_type = c_cv::default_image_type(img);
    }

    // converted to uint8 if base mat type != unsigned 8-bit int
    const cv::Mat* selected_mat;
    cv::Mat        converted_mat;

    auto mat_type = img.type();
    auto num_type = c_cv::cv2numeric(mat_type);
    auto channels = c_cv::type_channels(mat_type);

    if (num_type != c_f::numeric_type::uint8)
    {
        auto cv_convert_type = c_cv::make_type(num_type, img_type);

        img.convertTo(converted_mat, cv_convert_type);
        selected_mat = &converted_mat;
    }
    else
    {
        selected_mat = &img;
    }

    auto [internal_format, format] = gl_texture2d::get_format_from_img_type(img_type);

    glGenTextures(1, &(__handler));
    glBindTexture(GL_TEXTURE_2D, __handler);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        static_cast<GLint>(internal_format),
        img.cols,
        img.rows,
        0,
        format,
        GL_UNSIGNED_BYTE,
        img.data
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace callisto::graphics