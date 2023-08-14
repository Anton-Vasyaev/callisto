#pragma once

// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{
enum class gl_debug_source
{
    unknown,
    api,
    window_system,
    shader_compiler,
    third_party,
    application,
    other
};

inline constexpr gl_debug_source gl_debug_source_from_original(GLenum value) noexcept
{
    switch (value)
    {
        case GL_DEBUG_SOURCE_API : return gl_debug_source::api;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM : return gl_debug_source::window_system;
        case GL_DEBUG_SOURCE_SHADER_COMPILER : return gl_debug_source::shader_compiler;
        case GL_DEBUG_SOURCE_THIRD_PARTY : return gl_debug_source::third_party;
        case GL_DEBUG_SOURCE_APPLICATION : return gl_debug_source::application;
        case GL_DEBUG_SOURCE_OTHER : return gl_debug_source::other;

        default : return gl_debug_source::unknown;
    }
}

inline constexpr GLenum gl_debug_source_to_original(gl_debug_source debug_source) noexcept
{
    switch (debug_source)
    {
        case gl_debug_source::api : return GL_DEBUG_SOURCE_API;
        case gl_debug_source::window_system : return GL_DEBUG_SOURCE_WINDOW_SYSTEM;
        case gl_debug_source::shader_compiler : return GL_DEBUG_SOURCE_SHADER_COMPILER;
        case gl_debug_source::third_party : return GL_DEBUG_SOURCE_THIRD_PARTY;
        case gl_debug_source::application : return GL_DEBUG_SOURCE_APPLICATION;
        case gl_debug_source::other : return GL_DEBUG_SOURCE_OTHER;

        default : return 0;
    }
}

inline constexpr const char* gl_debug_source_str(gl_debug_source debug_source) noexcept
{
    switch (debug_source)
    {
        case gl_debug_source::api : return "api";
        case gl_debug_source::window_system : return "window_system";
        case gl_debug_source::shader_compiler : return "shader_compiler";
        case gl_debug_source::third_party : return "third_party";
        case gl_debug_source::application : return "application";
        case gl_debug_source::other : return "other";

        default : return "unknown";
    }
}

} // namespace callisto::graphics
