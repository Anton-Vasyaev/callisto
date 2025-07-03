#pragma once

// project
#include <callisto/framework/types/lifetime.hpp>

#include "../third_party/include_gl.hpp"

#include "gl_texture2d.hpp"
#include "gl_renderbuffer.hpp"

namespace callisto::graphics
{

class gl_framebuffer
{
    GLuint __handler;

public:
    // lifetime
    gl_framebuffer();

    ~gl_framebuffer();

    CALLISTO_LIFETIME_REFERENCE(gl_framebuffer);

    // methods
    void bind() { glBindFramebuffer(GL_FRAMEBUFFER, __handler); }

    void bind_color_texture(int index, gl_texture2d& texture);

    void unbind_color_texture(int index);

    void bind_depth_texture(gl_texture2d& texture);

    void unbind_depth_texture();

    void bind_color_renderbuffer(int index, gl_renderbuffer& buffer);

    void bind_depth_buffer(gl_renderbuffer& buffer);

    void check();

    // getters and setters
    GLuint get_handler() const { return __handler; }
};

} // namespace callisto::graphics
