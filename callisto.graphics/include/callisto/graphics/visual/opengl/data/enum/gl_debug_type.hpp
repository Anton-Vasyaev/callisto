#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

enum class gl_debug_type
{
    unknown,
    error,
    deprecated_behavior,
    undefined_behavior,
    portability,
    performance,
    marker,
    push_group,
    pop_group,
    other
};

inline constexpr gl_debug_type gl_debug_type_from_original(GLenum value) noexcept
{
    switch (value)
    {
        case GL_DEBUG_TYPE_ERROR : return gl_debug_type::error;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR : return gl_debug_type::deprecated_behavior;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR : return gl_debug_type::undefined_behavior;
        case GL_DEBUG_TYPE_PORTABILITY : return gl_debug_type::portability;
        case GL_DEBUG_TYPE_PERFORMANCE : return gl_debug_type::performance;
        case GL_DEBUG_TYPE_MARKER : return gl_debug_type::marker;
        case GL_DEBUG_TYPE_PUSH_GROUP : return gl_debug_type::push_group;
        case GL_DEBUG_TYPE_POP_GROUP : return gl_debug_type::pop_group;
        case GL_DEBUG_TYPE_OTHER : return gl_debug_type::other;

        default : return gl_debug_type::unknown;
    }
}

inline constexpr GLenum gl_debug_type_to_original(gl_debug_type debug_type) noexcept
{
    switch (debug_type)
    {
        case gl_debug_type::error : return GL_DEBUG_TYPE_ERROR;
        case gl_debug_type::deprecated_behavior : return GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR;
        case gl_debug_type::undefined_behavior : return GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR;
        case gl_debug_type::portability : return GL_DEBUG_TYPE_PORTABILITY;
        case gl_debug_type::performance : return GL_DEBUG_TYPE_PERFORMANCE;
        case gl_debug_type::marker : return GL_DEBUG_TYPE_MARKER;
        case gl_debug_type::push_group : return GL_DEBUG_TYPE_PUSH_GROUP;
        case gl_debug_type::pop_group : return GL_DEBUG_TYPE_POP_GROUP;
        case gl_debug_type::other : return GL_DEBUG_TYPE_OTHER;

        default : return 0;
    }
}

inline constexpr const char* gl_debug_type_str(gl_debug_type debug_type) noexcept
{
    switch (debug_type)
    {
        case gl_debug_type::error : return "error";
        case gl_debug_type::deprecated_behavior : return "deprecated_behavior";
        case gl_debug_type::undefined_behavior : return "undefined_behavior";
        case gl_debug_type::portability : return "portability";
        case gl_debug_type::performance : return "performance";
        case gl_debug_type::marker : return "marker";
        case gl_debug_type::push_group : return "push_group";
        case gl_debug_type::pop_group : return "pop_group";
        case gl_debug_type::other : return "other";

        default : return "unknown";
    }
}

} // namespace callisto::graphics