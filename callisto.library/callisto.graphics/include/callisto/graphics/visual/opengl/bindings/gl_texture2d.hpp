#pragma once

// std
#include <tuple>
// 3rd party
#include <boost/current_function.hpp>

#include <callisto/framework/exception.hpp>
#include <callisto/framework/string.hpp>
#include <callisto/opencv.hpp>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>
#include <callisto/graphics/visual/opengl/exception.hpp>

namespace callisto::graphics
{

class gl_texture2d
{
    GLuint __handler;

    struct conversion_formats
    {
        GLenum internal_format;
        GLenum format;
    };

    // static methods
    static conversion_formats
    get_format_from_img_type(callisto::opencv::image_type t, bool validate = true)
    {
        namespace c_f  = callisto::framework;
        namespace c_cv = callisto::opencv;

        switch (t)
        {
            case c_cv::image_type::bgr : return { GL_RGB, GL_BGR };
            case c_cv::image_type::bgra : return { GL_RGBA, GL_BGRA };
            case c_cv::image_type::rgb : return { GL_RGB, GL_RGB };
            case c_cv::image_type::rgba : return { GL_RGBA, GL_RGBA };
            case c_cv::image_type::grayscale : return { GL_RED, GL_RED };

            default :
                if (validate)
                {
                    CALLISTO_THROW_EXCEPTION(opengl_exception()) << c_f::error_tag_message(c_f::_bs(
                        "invalid img type for generate gl_texture2d:",
                        c_cv::image_type_str(t)
                    ));
                }
                else
                {
                    return { GL_FALSE, GL_FALSE };
                }
        }
    }

    // private methods
    void destruct() noexcept
    {
        if (__handler != 0)
        {
            glDeleteTextures(1, &(__handler));
        }
    }

    void move_from(gl_texture2d&& texture) noexcept
    {
        __handler         = texture.__handler;
        texture.__handler = 0;
    }

    void __initialize_data(const cv::Mat& img, callisto::opencv::image_type img_type);

public:
    // construct and destruct
    gl_texture2d() : __handler(0) {}

    gl_texture2d(const gl_texture2d&) = delete;

    gl_texture2d(gl_texture2d&& texture) noexcept { move_from(std::move(texture)); }

    explicit gl_texture2d(
        const cv::Mat&               img,
        callisto::opencv::image_type img_type = callisto::opencv::image_type::unknown
    )
    {
        __initialize_data(img, img_type);
    }

    explicit gl_texture2d(const callisto::opencv::mat_holder& holder)
    {
        holder.validate();

        __initialize_data(holder.mat(), holder.get_image_type());
    }

    ~gl_texture2d() noexcept { destruct(); }

    // methods
    void bind() { glBindTexture(GL_TEXTURE_2D, __handler); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void generate_mipmap() { glGenerateMipmap(GL_TEXTURE_2D); }

    // glTexParameteri getters & setters

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void set_texture_wrap_s(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void set_texture_wrap_t(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void set_texture_min_filter(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void set_texture_mag_filter(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    }

    // getters and setters
    GLuint get_handler() const { return __handler; }

    // operators
    gl_texture2d& operator=(const gl_texture2d&) = delete;

    gl_texture2d& operator=(gl_texture2d&& texture) noexcept
    {
        destruct();
        move_from(std::move(texture));

        return *this;
    }
};

} // namespace callisto::graphics