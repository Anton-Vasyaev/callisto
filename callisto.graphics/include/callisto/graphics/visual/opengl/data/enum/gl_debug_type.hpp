#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

// clang-format off

#define CALLISTO GL_DEBUG_TYPE_FUNCTIONS                                    \
    inline static constexpr gl_debug_type from_original(GLenum value);      \
                                                                            \
    inline constexpr GLenum original();                                     \

CALLISTO_DEFINE_OBJECT_ENUM(
    gl_debug_type,
    GL_DEBUG_TYPE_FUNCTIONS,
    (unknown),
    (error),
    (deprecated_behavior),
    (undefined_behavior),
    (portability),
    (performance),
    (marker),
    (push_group),
    (pop_group),
    (other),
);

// clang-format on

inline constexpr gl_debug_type gl_debug_type::from_original(int value)
{
    switch (value)
    {
        case GL_DEBUG_TYPE_ERROR : return gl_debug_type::error();
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR : return gl_debug_type::deprecated_behavior();
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR : return gl_debug_type::undefined_behavior();
        case GL_DEBUG_TYPE_PORTABILITY : return gl_debug_type::portability();
        case GL_DEBUG_TYPE_PERFORMANCE : return gl_debug_type::performance();
        case GL_DEBUG_TYPE_MARKER : return gl_debug_type::marker();
        case GL_DEBUG_TYPE_PUSH_GROUP : return gl_debug_type::push_group();
        case GL_DEBUG_TYPE_POP_GROUP : return gl_debug_type::pop_group();
        case GL_DEBUG_TYPE_OTHER : return gl_debug_type::other();

        default : return gl_debug_type::unknown();
    }
}

inline constexpr GLenum gl_debug_type::original()
{
    switch (_enum_data)
    {
        case inner::error : return GL_DEBUG_TYPE_ERROR;
        case inner::deprecated_behavior : return GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR;
        case inner::undefined_behavior : return GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR;
        case inner::portability : return GL_DEBUG_TYPE_PORTABILITY;
        case inner::performance : return GL_DEBUG_TYPE_PERFORMANCE;
        case inner::marker : return GL_DEBUG_TYPE_MARKER;
        case inner::push_group : return GL_DEBUG_TYPE_PUSH_GROUP;
        case inner::pop_group : return GL_DEBUG_TYPE_POP_GROUP;
        case inner::other : return GL_DEBUG_TYPE_OTHER;

        default : return 0;
    }
}

} // namespace callisto::graphics