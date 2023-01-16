#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

// clang-format off

#define CALLISTO GL_SHADER_TYPE_FUNCTIONS                                   \
    inline static constexpr gl_shader_type from_original(GLenum value);     \
                                                                            \
    inline constexpr GLenum original();                                     \

CALLISTO_DEFINE_OBJECT_ENUM(
    gl_shader_type,
    GL_SHADER_TYPE_FUNCTIONS,
    (unknown),
    (vertex),
    (fragment)
);

// clang-format on

inline static constexpr gl_shader_type gl_shader_type::from_original(GLenum value)
{
    switch (value)
    {
        case GL_VERTEX_SHADER : return gl_shader_type::vertex();
        case GL_FRAGMENT_SHADER : return gl_shader_type::fragment();
        default : return gl_shader_type::unknown();
    }
}

inline constexpr GLenum gl_shader_type::original()
{
    switch (_enum_data)
    {
        case inner::vertex : return GL_VERTEX_SHADER;
        case inner::fragment : return GL_FRAGMENT_SHADER;
        default : return 0;
    }
}

} // namespace callisto::graphics