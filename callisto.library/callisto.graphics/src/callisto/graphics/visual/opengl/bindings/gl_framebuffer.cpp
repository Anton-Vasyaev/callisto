// parent header
#include <callisto/graphics/visual/opengl/bindings/gl_framebuffer.hpp>

// project
#include <callisto/graphics/visual/opengl/gl_info_provider.hpp>

#include <callisto/graphics/visual/opengl/gl_operation_error_exception.hpp>

namespace callisto::graphics
{

namespace c_f = callisto::framework;

namespace
{

GLenum validate_index_and_get_attachment(int index)
{
    GLenum attachment = GL_COLOR_ATTACHMENT0;

    auto max_attachments
        = c_f::singleton<gl_info_provider>::get_instance().get_max_color_attachments();

    if (index >= max_attachments)
    {
        CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
            "index of color attachment >= max counts of color attachments: ",
            index,
            " >= ",
            max_attachments,
            "."
        );
    }
    attachment += index;

    return attachment;
}

} // namespace

#pragma region construct_and_destruct

gl_framebuffer::gl_framebuffer()
{
    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(glGenFramebuffers, 1, &__handler);
}

gl_framebuffer::~gl_framebuffer() { glDeleteFramebuffers(1, &__handler); }

#pragma endregion

#pragma methods

void gl_framebuffer::bind_color_texture(int index, gl_texture2d& texture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, __handler);
    glBindTexture(GL_TEXTURE_2D, texture.get_handler());

    auto tex_format = texture.get_format();

    if (tex_format != GL_RGB)
    {
        CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
            "invalid texture format for framebuffer binging, code:",
            static_cast<int>(tex_format)
        );
    }

    auto attachment = validate_index_and_get_attachment(index);

    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(
        glFramebufferTexture2D,
        GL_FRAMEBUFFER,
        attachment,
        GL_TEXTURE_2D,
        texture.get_handler(),
        0
    );
}

void gl_framebuffer::unbind_color_texture(int index)
{
    CALLISTO_THROW_EXCEPTION(c_f::not_implemented_exception());
}

void gl_framebuffer::bind_depth_texture(gl_texture2d& texture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, __handler);
    glBindTexture(GL_TEXTURE_2D, texture.get_handler());

    auto tex_format = texture.get_format();

    GLenum attachment;

    switch (tex_format)
    {
        case GL_DEPTH :
        {
            attachment = GL_DEPTH_ATTACHMENT;
            break;
        }
        case GL_DEPTH_STENCIL :
        {
            attachment = GL_DEPTH_STENCIL_ATTACHMENT;
            break;
        }
        default :
            CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
                "invalid format of depth texture for framebuffer binding, code:",
                static_cast<int>(tex_format)
            );
    }

    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(
        glFramebufferTexture2D,
        GL_FRAMEBUFFER,
        attachment,
        GL_TEXTURE_2D,
        texture.get_handler(),
        0
    );
}

void gl_framebuffer::unbind_depth_texture()
{
    CALLISTO_THROW_EXCEPTION(c_f::not_implemented_exception());
}

void gl_framebuffer::bind_color_renderbuffer(int index, gl_renderbuffer& buffer)
{
    bool validate = false;
    auto format   = buffer.get_format();
    if (format == GL_RGB8 || format == GL_RGBA8)
    {
        validate = true;
    }

    if (!validate)
    {
        CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
            "invalid format of renderbuffer for framebuffer binging, code:",
            static_cast<int>(buffer.get_format())
        );
    }

    auto attachment = validate_index_and_get_attachment(index);

    glBindFramebuffer(GL_FRAMEBUFFER, __handler);

    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(
        glFramebufferRenderbuffer,
        GL_FRAMEBUFFER,
        attachment,
        GL_RENDERBUFFER,
        buffer.get_handler()
    );

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gl_framebuffer::bind_depth_buffer(gl_renderbuffer& buffer)
{
    auto render_format = buffer.get_format();

    GLenum attachment;

    switch (render_format)
    {
        case GL_DEPTH_COMPONENT16 :
        case GL_DEPTH_COMPONENT24 :
        case GL_DEPTH_COMPONENT32F :
        {
            attachment = GL_DEPTH_ATTACHMENT;
            break;
        }

        case GL_DEPTH24_STENCIL8 :
        case GL_DEPTH32F_STENCIL8 :
        {
            attachment = GL_DEPTH_ATTACHMENT;
            break;
        }
        default :
        {
            CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
                "Invalid format of depth renderbuffer for framebuffer binding, code:",
                static_cast<int>(render_format)
            );
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, __handler);

    CALLISTO_GRAPHICS_WRAP_GL_OPERATION(
        glFramebufferRenderbuffer,
        GL_FRAMEBUFFER,
        attachment,
        GL_RENDERBUFFER,
        buffer.get_handler()
    );
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gl_framebuffer::check()
{
    glBindFramebuffer(GL_FRAMEBUFFER, __handler);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
            << c_f::build_error_tag_message("opengl Framebuffer is not complete.");
    }
}

#pragma endregion

} // namespace callisto::graphics