// parent header
#include <callisto/graphics/visual/opengl/bindings/gl_shader.hpp>
// project
#include <callisto/graphics/visual/opengl/exception.hpp>

namespace callisto::graphics
{

gl_shader::gl_shader(const char* source, gl_shader_type shader_type)
{
    __handler = glCreateShader(gl_shader_type_to_original(shader_type));
    glShaderSource(__handler, 1, &source, nullptr);
    glCompileShader(__handler);

    GLint success_status;
    glGetShaderiv(__handler, GL_COMPILE_STATUS, &success_status);

    if (!static_cast<bool>(success_status))
    {
        GLint info_log_length = 0;
        glGetShaderiv(__handler, GL_INFO_LOG_LENGTH, &info_log_length);

        std::string info_log;
        info_log.resize(info_log_length);

        glGetShaderInfoLog(__handler, info_log_length, nullptr, info_log.data());

        CALLISTO_THROW_EXCEPTION(
            opengl_shader_failed_compilation_exception(shader_type, std::move(info_log))
        );
    }
}

} // namespace callisto::graphics
