#pragma once

// std
#include <cstdint>
// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

enum class gl_error_type : std::uint8_t
{
    unknown,
    invalid_enum,
    invalid_value,
    invalid_operation,
    invalid_framebuffer_operation,
    out_of_memory,
    stack_underflow,
    stack_overflow
};

constexpr gl_error_type gl_error_type_from_original(GLenum value) noexcept
{
    switch (value)
    {
        case GL_INVALID_ENUM : return gl_error_type::invalid_enum;
        case GL_INVALID_VALUE : return gl_error_type::invalid_value;
        case GL_INVALID_OPERATION : return gl_error_type::invalid_operation;
        case GL_INVALID_FRAMEBUFFER_OPERATION : return gl_error_type::invalid_framebuffer_operation;
        case GL_OUT_OF_MEMORY : return gl_error_type::out_of_memory;
        case GL_STACK_UNDERFLOW : return gl_error_type::stack_underflow;
        case GL_STACK_OVERFLOW : return gl_error_type::stack_overflow;

        default : return gl_error_type::unknown;
    }
}

constexpr GLenum gl_error_type_to_original(gl_error_type error_type)
{
    switch (error_type)
    {
        case gl_error_type::invalid_enum : return GL_INVALID_ENUM;
        case gl_error_type::invalid_value : return GL_INVALID_VALUE;
        case gl_error_type::invalid_operation : return GL_INVALID_OPERATION;
        case gl_error_type::invalid_framebuffer_operation : return GL_INVALID_FRAMEBUFFER_OPERATION;
        case gl_error_type::out_of_memory : return GL_OUT_OF_MEMORY;
        case gl_error_type::stack_underflow : return GL_STACK_UNDERFLOW;
        case gl_error_type::stack_overflow : return GL_STACK_OVERFLOW;

        default : return 0;
    }
}

constexpr const char* gl_error_type_str(gl_error_type error_type)
{
    switch (error_type)
    {
        case gl_error_type::invalid_enum : return "invalid_enum";
        case gl_error_type::invalid_value : return "invalid_value";
        case gl_error_type::invalid_operation : return "invalid_operation";
        case gl_error_type::invalid_framebuffer_operation : return "invalid_framebuffer_operation";
        case gl_error_type::out_of_memory : return "out_of_memory";
        case gl_error_type::stack_underflow : return "stack_underflow";
        case gl_error_type::stack_overflow : return "stack_overflow";

        default : return "";
    }
}

} // namespace callisto::graphics