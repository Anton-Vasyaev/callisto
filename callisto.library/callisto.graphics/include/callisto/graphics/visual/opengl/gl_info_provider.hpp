#pragma once

// project
#include <callisto/framework/types/lifetime.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

class gl_info_provider
{
    GLint __max_color_attachments;

    GLint __max_samples;

public:
    // lifetime
    gl_info_provider();

    CALLISTO_LIFETIME_REFERENCE(gl_info_provider);

    // methods
    int get_max_color_attachments() const { return __max_color_attachments; }

    int get_max_samples() const { return __max_samples; }
};

} // namespace callisto::graphics