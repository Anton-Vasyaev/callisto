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
    gl_renderbuffer(GLenum format, size_t width, size_t height, int samples)
    {
        __format = format;

        glGenRenderbuffers(1, &__handler);
        glBindRenderbuffer(GL_RENDERBUFFER, __handler);

        glRenderbufferStorageMultisample(
            GL_RENDERBUFFER,
            samples,
            format,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height)
        );

        // TODO
        auto err = glGetError();
        if (err)
        {
            std::cout << "err:"
                      << "glRenderBufferStorageMultiSample err\n";
        }
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    ~gl_renderbuffer() { glDeleteRenderbuffers(1, &__handler); }

    CALLISTO_LIFETIME_REFERENCE(gl_renderbuffer);

    // getters
    GLuint get_handler() const { return __handler; }

    GLenum get_format() const { return __format; }
};
} // namespace callisto::graphics