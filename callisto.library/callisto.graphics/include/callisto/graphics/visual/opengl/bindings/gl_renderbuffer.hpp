#pragma once

#include <callisto/framework/types/lifetime.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{
class gl_renderbuffer
{
    GLuint __handler;

    GLenum __format;

public:
    gl_renderbuffer(GLenum format, size_t width, size_t height)
    {
        __format = format;

        glGenRenderbuffers(1, &__handler);
        glBindRenderbuffer(GL_RENDERBUFFER, __handler);
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            format,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height)
        );
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    ~gl_renderbuffer() { glDeleteRenderbuffers(1, &__handler); }

    CALLISTO_LIFETIME_REFERENCE(gl_renderbuffer);

    // getters
    GLuint get_handler() const { return __handler; }

    GLenum get_format() const { return __format; }
};
} // namespace callisto::graphics