#pragma once

// std
#include <cstdint>
// project
#include <callisto/framework/configuration/object_enum.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

// clang-format off

#define CALLISTO_GL_DEBUG_SEVERITY_FUNCTIONS                                                \
    inline static constexpr gl_debug_severity from_original(GLenum value) noexcept;         \
                                                                                            \
    inline constexpr GLenum original() const noexcept;                                      

CALLISTO_DEFINE_OBJECT_ENUM(
    gl_debug_severity,
    CALLISTO_GL_DEBUG_SEVERITY_FUNCTIONS,
    (unknown),
    (high),
    (medium),
    (low),
    (notification)
);


// clang-format on

inline constexpr gl_debug_severity gl_debug_severity::from_original(GLenum value) noexcept
{
    switch (value)
    {
        case GL_DEBUG_SEVERITY_HIGH : return gl_debug_severity::high();
        case GL_DEBUG_SEVERITY_MEDIUM : return gl_debug_severity::medium();
        case GL_DEBUG_SEVERITY_LOW : return gl_debug_severity::low();
        case GL_DEBUG_SEVERITY_NOTIFICATION : return gl_debug_severity::notification();

        default : return gl_debug_severity::unknown();
    }
}

inline constexpr GLenum gl_debug_severity::original() const noexcept
{
    switch (_enum_data)
    {
        case inner::high : return GL_DEBUG_SEVERITY_HIGH;
        case inner::medium : return GL_DEBUG_SEVERITY_MEDIUM;
        case inner::low : return GL_DEBUG_SEVERITY_LOW;
        case inner::notification : return GL_DEBUG_SEVERITY_NOTIFICATION;

        default : return 0;
    }
}

} // namespace callisto::graphics