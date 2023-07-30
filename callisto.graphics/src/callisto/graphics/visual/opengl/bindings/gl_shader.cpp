// parent header
#include <callisto/graphics/visual/opengl/bindings/gl_shader.hpp>
// 3rd party
#include <callisto/framework/string.hpp>

namespace callisto::graphics
{

gl_shader::gl_shader(const char* source, gl_shader_type shader_type)
{
    this->handler = glCreateShader(gl_shader_type_to_original(shader_type));
    glShaderSource(this->handler, 1, &source, nullptr);
    glCompileShader(this->handler);

    GLint  success_status;
    GLchar info_log[gl_shader::INFO_LOG_SIZE];
    glGetShaderiv(this->handler, GL_COMPILE_STATUS, &success_status);

    if (!success_status)
    {
        glGetShaderInfoLog(this->handler, INFO_LOG_SIZE, nullptr, info_log);
        throw c_f::exception() << c_f::error_tag_message(c_f::_bs(
            "Failed to compilation, ",
            gl_shader_type_str(shader_type),
            " shader:",
            info_log,
            "."
        ));
    }
}

} // namespace callisto::graphics
