#pragma once

// std
#include <cstdint>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

enum class gl_shader_type : std::uint8_t
{
    unknown,
    vertex,
    fragment
};

constexpr gl_shader_type gl_shader_type_from_original(GLenum value) noexcept
{
    switch (value)
    {
        case GL_VERTEX_SHADER : return gl_shader_type::vertex;
        case GL_FRAGMENT_SHADER : return gl_shader_type::fragment;
        default : return gl_shader_type::unknown;
    }
}

constexpr GLenum gl_shader_type_to_original(gl_shader_type shader_type) noexcept
{
    switch (shader_type)
    {
        case gl_shader_type::vertex : return GL_VERTEX_SHADER;
        case gl_shader_type::fragment : return GL_FRAGMENT_SHADER;
        default : return 0;
    }
}

constexpr const char* gl_shader_type_str(gl_shader_type shader_type) noexcept
{
    switch (shader_type)
    {
        case gl_shader_type::fragment : return "fragment";
        case gl_shader_type::vertex : return "vertex";

        default : return "unknown";
    }
}

} // namespace callisto::graphics