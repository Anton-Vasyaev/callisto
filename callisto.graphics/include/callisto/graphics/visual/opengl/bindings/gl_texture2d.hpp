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

namespace
{
namespace c_f  = callisto::framework;
namespace c_cv = callisto::opencv;
} // namespace

class gl_texture2d
{
    GLuint handler;

    struct conversion_formats
    {
        GLenum internal_format;
        GLenum format;
    };

    // static methods
    inline static conversion_formats get_format_from_img_type(c_cv::image_type t)
    {
        switch (t)
        {
            case c_cv::image_type::bgr : return { GL_RGB, GL_BGR };
            case c_cv::image_type::bgra : return { GL_RGBA, GL_BGRA };
            case c_cv::image_type::rgb : return { GL_RGB, GL_RGB };
            case c_cv::image_type::rgba : return { GL_RGBA, GL_RGBA };
            case c_cv::image_type::grayscale : return { GL_RED, GL_RED };

            default :
                throw opengl_exception() << c_f::error_tag_message(
                    c_f::_bs("invalid img type for generate gl_texture2d:", c_cv::image_type_str(t))
                ) << c_f::error_tag_function_name(BOOST_CURRENT_FUNCTION);
        }
    }

    // private methods
    inline void destruct()
    {
        if (this->handler != 0) { glDeleteTextures(1, &(this->handler)); }
    }

    inline void move_from(gl_texture2d&& texture)
    {
        this->handler   = texture.handler;
        texture.handler = 0;
    }

public:
    // deleted functions
    gl_texture2d(const gl_texture2d&) = delete;

    gl_texture2d& operator=(const gl_texture2d&) = delete;

    // construct and destruct
    inline gl_texture2d() : handler(0) {}

    inline gl_texture2d(gl_texture2d&& texture) { this->move_from(std::move(texture)); }

    gl_texture2d(const cv::Mat& img, c_cv::image_type img_type = c_cv::image_type::unknown);

    inline gl_texture2d(const c_cv::mat_holder& holder)
    {
        holder.validate(BOOST_CURRENT_FUNCTION);

        gl_texture2d(holder.mat(), holder.image_type());
    }

    inline ~gl_texture2d() { this->destruct(); }

    // methods
    inline void bind() { glBindTexture(GL_TEXTURE_2D, this->handler); }

    inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

    inline void generate_mipmap() { glGenerateMipmap(GL_TEXTURE_2D); }

    // glTexParameteri getters & setters
    inline void set_texture_wrap_s(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
    }

    inline void set_texture_wrap_t(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
    }

    inline void set_texture_min_filter(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    }

    inline void set_texture_mag_filter(GLint param)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    }

    // operators
    inline gl_texture2d& operator=(gl_texture2d&& texture)
    {
        this->destruct();
        this->move_from(std::move(texture));

        return *this;
    }
};

} // namespace callisto::graphics