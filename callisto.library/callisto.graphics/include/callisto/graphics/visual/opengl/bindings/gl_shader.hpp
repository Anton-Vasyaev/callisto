#pragma once

// std
#include <fstream>
#include <sstream>
// 3rd party
#include <callisto/framework/exception.hpp>
#include <callisto/framework/string.hpp>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>
#include <callisto/graphics/visual/opengl/data.hpp>

namespace callisto::graphics
{

class gl_shader
{
    GLuint __handler;

    void move_from(gl_shader&& shader) noexcept
    {
        __handler        = shader.__handler;
        shader.__handler = 0;
    }

    void destruct() noexcept
    {
        if (__handler != 0)
        {
            glDeleteShader(__handler);
        }
    }

public:
#pragma region static_methods

    template<typename str_type>
    static gl_shader load_from_file(str_type& shader_path, gl_shader_type shader_type)
    {
        namespace c_f = callisto::framework;

        std::fstream file(shader_path);

        if (!file.is_open())
        {
            CALLISTO_THROW_EXCEPTION(c_f::not_find_exception()
            ) << c_f::error_tag_message_w(c_f::_wbs("failed to open file with shader:", shader_path)
            );
        }
        std::stringstream ss;
        ss << file.rdbuf();

        return gl_shader(ss.str().c_str(), shader_type);
    }

#pragma endregion

    // deleted functions
    gl_shader(const gl_shader&) = delete;

    gl_shader& operator=(const gl_shader&) = delete;

    // construct and destruct
    gl_shader() : __handler(0) {}

    gl_shader(gl_shader&& shader) noexcept { move_from(std::move(shader)); }

    gl_shader(const char* source, gl_shader_type shader_type);

    ~gl_shader() noexcept { destruct(); }

    // getters and setters
    GLuint get_handler() const { return __handler; }

    // operators
    gl_shader& operator=(gl_shader&& shader) noexcept
    {
        destruct();
        move_from(std::move(shader));

        return *this;
    }
};

} // namespace callisto::graphics