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

namespace
{
namespace c_f = callisto::framework;
}

class gl_shader
{
    static constexpr size_t INFO_LOG_SIZE = 1024;

    GLuint handler;

    inline void move_from(gl_shader&& shader)
    {
        this->handler  = shader.handler;
        shader.handler = 0;
    }

    inline void destruct()
    {
        if (this->handler != 0)
        {
            glDeleteShader(this->handler);
        }
    }

public:
#pragma region static_methods

    template<typename str_type>
    static gl_shader load_from_file(str_type& shader_path, gl_shader_type shader_type)
    {
        std::fstream file(shader_path);

        if (!file.is_open())
        {
            throw c_f::exception() << c_f::error_tag_message_w(
                c_f::_wbs("failed to open file with shader:", shader_path)
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
    gl_shader() : handler(0) {}

    inline gl_shader(gl_shader&& shader) { this->move_from(std::move(shader)); }

    gl_shader(const char* source, gl_shader_type shader_type);

    inline ~gl_shader() { this->destruct(); }

    // getters and setters
    inline GLuint get_handler() const { return this->handler; }

    // operators
    inline gl_shader& operator=(gl_shader&& shader)
    {
        this->destruct();
        this->move_from(std::move(shader));

        return *this;
    }
};

} // namespace callisto::graphics