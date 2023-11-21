// parent header
#include <callisto/graphics/visual/opengl/bindings/gl_shader_program.hpp>
// project
#include <callisto/graphics/visual/opengl/exception.hpp>

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
        GLint log_length = 0;
        glGetShaderiv(this->handler, GL_INFO_LOG_LENGTH, &log_length);

        std::string info_log;
        info_log.resize(log_length);

        GLsizei real_len;
        glGetShaderInfoLog(this->handler, log_length, &real_len, info_log.data());

        glDeleteProgram(this->handler);

        CALLISTO_THROW_EXCEPTION(opengl_shader_failed_link_exception(std::move(info_log)));
    }
}

} // namespace callisto::graphics