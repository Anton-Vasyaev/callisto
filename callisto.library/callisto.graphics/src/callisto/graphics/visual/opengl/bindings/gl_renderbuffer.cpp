// parent header
#include <callisto/graphics/visual/opengl/bindings/gl_renderbuffer.hpp>
// project
#include <callisto/graphics/visual/opengl/gl_operation_error_exception.hpp>

namespace callisto::graphics
{
gl_renderbuffer::gl_renderbuffer(GLenum format, size_t width, size_t height, int samples)
{
    __format = format;

    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(glGenRenderbuffers, 1, &__handler);
    glBindRenderbuffer(GL_RENDERBUFFER, __handler);

    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(
        glRenderbufferStorageMultisample,
        GL_RENDERBUFFER,
        samples,
        format,
        static_cast<GLsizei>(width),
        static_cast<GLsizei>(height)
    );

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

gl_renderbuffer::~gl_renderbuffer() { glDeleteRenderbuffers(1, &__handler); }
} // namespace callisto::graphics