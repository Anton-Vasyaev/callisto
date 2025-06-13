// parent header
#include <callisto/graphics/visual/opengl/gl_info_provider.hpp>

// project
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

gl_info_provider::gl_info_provider()
{
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &__max_color_attachments);

    glGetIntegerv(GL_MAX_SAMPLES, &__max_samples);
}

} // namespace callisto::graphics