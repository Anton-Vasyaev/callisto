#pragma once

// project
#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/types/singleton.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

class gl_info_provider : public callisto::framework::singleton<gl_info_provider>
{
    friend class singleton<gl_info_provider>;

    GLint __max_color_attachments;

    GLint __max_samples;

protected:
    gl_info_provider();

public:
    // lifetime

    CALLISTO_LIFETIME_REFERENCE(gl_info_provider);

    // methods
    int get_max_color_attachments() const { return __max_color_attachments; }

    int get_max_samples() const { return __max_samples; }
};

} // namespace callisto::graphics