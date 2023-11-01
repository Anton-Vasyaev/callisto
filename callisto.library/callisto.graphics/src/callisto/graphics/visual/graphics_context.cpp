// parent header
#include <callisto/graphics/visual/graphics_context.hpp>
// project
#include <callisto/graphics/visual/opengl/gl_main_context.hpp>

namespace callisto::graphics
{

graphics_context::graphics_context() {}

i_main_context& graphics_context::get_context(const char* context_name)
{
    if (this->contexts.contains(context_name)) return *(this->contexts[context_name]);

    if (std::string_view(context_name) == "opengl")
    {
        this->contexts.insert({ context_name, std::make_unique<gl_main_context>() });
    }

    return *(this->contexts["opengl"]);
}

} // namespace callisto::graphics