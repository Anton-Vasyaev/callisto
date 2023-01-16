// parent header
#include <callisto/graphics/opengl/bindings/gl_shader_program.hpp>
// 3rd party
#include <callisto/framework/string.hpp>

namespace callisto::graphics
{

gl_shader_program::gl_shader_program(gl_shader& vertex_shader, gl_shader& fragment_shader)
{
    this->handler = glCreateProgram();

    glAttachShader(this->handler, vertex_shader.get_handler());
    glAttachShader(this->handler, fragment_shader.get_handler());
    glLinkProgram(this->handler);

    GLint success_status;
    glGetProgramiv(this->handler, GL_LINK_STATUS, &success_status);
    if (!success_status)
    {
        GLchar info_log[INFO_LOG_SIZE];
        glGetShaderInfoLog(this->handler, INFO_LOG_SIZE, nullptr, info_log);

        glDeleteProgram(this->handler);

        throw c_f::exception(
        ) << c_f::error_tag_message(c_f::_bs("Failed to link shader program:", info_log, "."));
    }
}

} // namespace terramagnia::graphics