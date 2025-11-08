#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// project
#include <callisto/framework/exception.hpp>
#include <callisto/framework/string.hpp>

#include <callisto/math/primitives.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>
#include <callisto/graphics/visual/opengl/exception.hpp>

#include "gl_location.hpp"
#include "gl_shader.hpp"

namespace callisto::graphics
{

class gl_shader_program
{
    GLuint handler;

    void move_from(gl_shader_program&& program) noexcept
    {
        this->handler   = program.handler;
        program.handler = 0;
    }

    void destruct() noexcept
    {
        if (this->handler != 0)
        {
            glDeleteProgram(this->handler);
        }
    }

public:
    // deleted functions
    gl_shader_program(const gl_shader_program&) = delete;

    gl_shader_program& operator=(const gl_shader_program&) = delete;

    // construct and destruct
    gl_shader_program() : handler(0) {}

    gl_shader_program(gl_shader& vertex_shader, gl_shader& fragment_shader);

    gl_shader_program(gl_shader_program&& program) noexcept { this->move_from(std::move(program)); }

    ~gl_shader_program() noexcept { this->destruct(); }

    // methods
    void use() const { glUseProgram(this->handler); }

    gl_location get_uniform_location_nothrow(const char* uniform_name)
    {
        auto location_idx = glGetUniformLocation(this->handler, uniform_name);

        return gl_location(location_idx);
    }

    gl_location get_uniform_location(const char* uniform_name)
    {
        namespace c_f = callisto::framework;
        auto location = get_uniform_location_nothrow(uniform_name);

        if (!location.is_exist())
        {
            CALLISTO_THROW_EXCEPTION(opengl_exception())
                << c_f::error_tag_message(c_f::_bs("Location is not exist:", uniform_name));
        }

        return location;
    }

    // matrix
    template<typename int_type>
    void uniform_matrix_4fv(int_type location, GLsizei count, bool transpose, float* matrix_ptr)
    {
        glUniformMatrix4fv(
            static_cast<GLint>(location),
            count,
            static_cast<GLboolean>(transpose),
            matrix_ptr
        );
    }

    template<typename int_type>
    void uniform_matrix_4fv(int_type location, GLsizei count, bool transpose, glm::mat4& mat)
    {
        glUniformMatrix4fv(
            static_cast<GLint>(location),
            count,
            static_cast<GLboolean>(transpose),
            glm::value_ptr(mat)
        );
    }

    // getters and settters
    GLuint get_handler() const { return this->handler; }

    // operator
    gl_shader_program& operator=(gl_shader_program&& program) noexcept
    {
        this->destruct();
        this->move_from(std::move(program));

        return *this;
    }
};

}; // namespace callisto::graphics