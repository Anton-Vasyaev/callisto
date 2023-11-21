#pragma once

// project
#include <callisto/framework/exception.hpp>
#include <callisto/graphics/visual/opengl/data/enum/gl_shader_type.hpp>

namespace callisto::graphics
{
namespace
{
namespace c_f = callisto::framework;
}

/// -----------------------------------------------------------------------------------------------

/// @brief Present opengl exception
struct opengl_exception : public virtual c_f::exception
{
};

/// -----------------------------------------------------------------------------------------------

/// @brief Present failed linkage of shader exception
struct opengl_shader_failed_link_exception : public virtual opengl_exception
{
    std::string error_log;

    opengl_shader_failed_link_exception(const std::string& error_log) : error_log(error_log) {}

    opengl_shader_failed_link_exception(std::string&& error_log)
    {
        this->error_log = std::move(error_log);
    }

    virtual std::string form_error_message() const
    {
        return c_f::_bs("failed to link shader. error log:", error_log);
    }
};

/// -----------------------------------------------------------------------------------------------

/// @brief Present failed compile of shader exception
struct opengl_shader_failed_compilation_exception : public virtual opengl_exception
{
    std::string error_log;

    gl_shader_type shader_type;

    opengl_shader_failed_compilation_exception(
        gl_shader_type     shader_type,
        const std::string& error_log
    ) :
        shader_type(shader_type), error_log(error_log)
    {
    }

    opengl_shader_failed_compilation_exception(gl_shader_type shader_type, std::string&& error_log)
    {
        this->shader_type = shader_type;
        this->error_log   = std::move(error_log);
    }

    virtual std::string form_error_message() const
    {
        return c_f::_bs(
            "failed to compile shader. type = ",
            gl_shader_type_str(shader_type),
            ". error log:",
            error_log
        );
    }
};

} // namespace callisto::graphics