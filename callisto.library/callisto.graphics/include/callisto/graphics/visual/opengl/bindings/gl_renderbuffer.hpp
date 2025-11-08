#pragma once

#include <callisto/framework/types/lifetime.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

// todo
#include <iostream>

namespace callisto::graphics
{
class gl_renderbuffer
{
    GLuint __handler;

    GLenum __format;

public:
    // construct and destruct
    gl_renderbuffer(GLenum format, size_t width, size_t height, int samples);

    ~gl_renderbuffer();

    // lifetime
    CALLISTO_LIFETIME_REFERENCE(gl_renderbuffer);

    // getters
    GLuint get_handler() const { return __handler; }

    GLenum get_format() const { return __format; }
};
} // namespace callisto::graphics