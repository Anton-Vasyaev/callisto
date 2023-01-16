#pragma once

// 3rd party
#include <callisto/math/primitives.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>
#include "gl_shader.hpp"

namespace callisto::graphics
{

namespace
{
namespace c_m = callisto::math;
}

class gl_shader_program
{
    GLuint handler;

    static constexpr size_t INFO_LOG_SIZE = 1024;

    inline void move_from(gl_shader_program&& program)
    {
        this->handler   = program.handler;
        program.handler = 0;
    }

    inline void destruct()
    {
        if (this->handler != 0) { glDeleteProgram(this->handler); }
    }

public:
    // deleted functions
    gl_shader_program(const gl_shader_program&) = delete;

    gl_shader_program& operator=(const gl_shader_program&) = delete;

    // construct and destruct
    inline gl_shader_program() : handler(0) {}

    gl_shader_program(gl_shader& vertex_shader, gl_shader& fragment_shader);

    inline gl_shader_program(gl_shader_program&& program) { this->move_from(std::move(program)); }

    inline ~gl_shader_program() { this->destruct(); }

    // methods
    inline void use() { glUseProgram(this->handler); }

    inline GLint get_uniform_location(const char* uniform_name)
    {
        return glGetUniformLocation(this->handler, uniform_name);
    }

    template<typename int_type>
    inline void uniform_1f(int_type location, float value)
    {
        glUniform1f(static_cast<GLint>(location), value);
    }

    template<typename int_type>
    inline void uniform_1i(int_type location, int value)
    {
        glUniform1i(static_cast<GLint>(location), value);
    }

    template<typename int_type, typename vec2f_type>
    inline void uniform_2f(int_type location, vec2f_type value)
    {
        auto [v1, v2] = value;
        glUniform2f(static_cast<GLint>(location), v1, v2);
    }

    template<typename int_type>
    inline void uniform_2f(int_type location, float v1, float v2)
    {
        glUniform2f(static_cast<GLint>(location), v1, v2);
    }

    template<typename int_type, typename num_type>
    inline void uniform_2f(int_type location, c_m::vector2<num_type> values)
    {
        float v1 = values.value1;
        float v2 = values.value2;

        glUniform2f(static_cast<GLint>(location), v1, v2);
    }

    template<typename int_type, typename vec3f_type>
    inline void uniform_3f(int_type location, vec3f_type value)
    {
        auto [v1, v2, v3] = value;
        glUniform3f(location, v1, v2, v3);
    }

    // matrix
    template<typename int_type>
    inline void
    uniform_matrix_4fv(int_type location, GLsizei count, bool transpose, float* matrix_ptr)
    {
        glUniformMatrix4fv(
            static_cast<GLint>(location),
            count,
            static_cast<GLboolean>(transpose),
            matrix_ptr
        );
    }

    template<typename int_type>
    inline void uniform_matrix_4fv(int_type location, GLsizei count, bool transpose, glm::mat4& mat)
    {
        glUniformMatrix4fv(
            static_cast<GLint>(location),
            count,
            static_cast<GLboolean>(transpose),
            glm::value_ptr(mat)
        );
    }

    // getters and settters
    inline GLuint get_handler() { return this->handler; }

    inline const GLuint get_handler() const { return this->handler; }

    // operator
    inline gl_shader_program& operator=(gl_shader_program&& program)
    {
        this->destruct();
        this->move_from(std::move(program));

        return *this;
    }
};

}; // namespace callisto::graphics