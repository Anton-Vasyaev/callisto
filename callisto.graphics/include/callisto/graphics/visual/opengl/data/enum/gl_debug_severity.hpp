#pragma once

// std
#include <cstdint>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{
enum class gl_debug_severity
{
    unknown,
    high,
    medium,
    low,
    notification
};

inline constexpr gl_debug_severity gl_debug_severity_from_original(GLenum value) noexcept
{
    switch (value)
    {
        case GL_DEBUG_SEVERITY_HIGH : return gl_debug_severity::high;
        case GL_DEBUG_SEVERITY_MEDIUM : return gl_debug_severity::medium;
        case GL_DEBUG_SEVERITY_LOW : return gl_debug_severity::low;
        case GL_DEBUG_SEVERITY_NOTIFICATION : return gl_debug_severity::notification;

        default : return gl_debug_severity::unknown;
    }
}

inline constexpr GLenum gl_debug_severity_to_original(gl_debug_severity severity) noexcept
{
    switch (severity)
    {
        case gl_debug_severity::high : return GL_DEBUG_SEVERITY_HIGH;
        case gl_debug_severity::medium : return GL_DEBUG_SEVERITY_MEDIUM;
        case gl_debug_severity::low : return GL_DEBUG_SEVERITY_LOW;
        case gl_debug_severity::notification : return GL_DEBUG_SEVERITY_NOTIFICATION;

        default : return 0;
    }
}

inline constexpr const char* gl_debug_severity_str(gl_debug_severity severity) noexcept
{
    switch (severity)
    {
        case gl_debug_severity::high : return "high";
        case gl_debug_severity::medium : return "medium";
        case gl_debug_severity::low : return "low";
        case gl_debug_severity::notification : return "notification";

        default : return "unknown";
    }
}

} // namespace callisto::graphics