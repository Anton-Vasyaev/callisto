#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

// clang-format off

#define CALLISTO GL_DEBUG_SOURCE_FUNCTIONS                                  \
    inline static constexpr gl_debug_source from_original(GLenum value);    \
                                                                            \
    inline constexpr GLenum original();                                     \

CALLISTO_DEFINE_OBJECT_ENUM(
    gl_debug_source,
    GL_DEBUG_SOURCE_FUNCTIONS,
    (unknown),
    (api),
    (window_system),
    (shader_compiler),
    (third_party),
    (application),
    (other)
);

// clang-format on

inline constexpr gl_debug_source gl_debug_source::from_original(GLenum value)
{
    switch (value)
    {
        case GL_DEBUG_SOURCE_API : return gl_debug_source::api();
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM : return gl_debug_source::window_system();
        case GL_DEBUG_SOURCE_SHADER_COMPILER : return gl_debug_source::shader_compiler();
        case GL_DEBUG_SOURCE_THIRD_PARTY : return gl_debug_source::third_party();
        case GL_DEBUG_SOURCE_APPLICATION : return gl_debug_source::application();
        case GL_DEBUG_SOURCE_OTHER : return gl_debug_source::other();

        default : return gl_debug_source::unknown();
    }
}

inline constexpr GLenum gl_debug_source::original()
{
    switch (_enum_data)
    {
        case inner::api : return GL_DEBUG_SOURCE_API;
        case inner::window_system : return GL_DEBUG_SOURCE_WINDOW_SYSTEM;
        case inner::shader_compiler : return GL_DEBUG_SOURCE_SHADER_COMPILER;
        case inner::third_party : return GL_DEBUG_SOURCE_THIRD_PARTY;
        case inner::application : return GL_DEBUG_SOURCE_APPLICATION;
        case inner::other : return GL_DEBUG_SOURCE_OTHER;

        default : return 0;
    }
}

} // namespace callisto::graphics
