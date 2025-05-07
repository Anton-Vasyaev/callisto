// parent header
#include <callisto/graphics/visual/opengl/gl_monitor_context.hpp>
// std
#include <iostream>
// project
#include <callisto/framework/exception.hpp>

#include <callisto/graphics/visual/opengl/data/gl_window_options.hpp>

namespace c_f = callisto::framework;

namespace callisto::graphics
{

#pragma region auxiliary_functions

namespace
{
struct PRESENTS_OF_AUXILIARY_OPTIONS
{
    static constexpr std::string_view IMGUI = "imgui";
};

void check_and_get_auxiliary_options(
    std::unordered_map<std::string_view, std::any>* auxiliary_options,
    gl_window_options&                              options
)

{
    if (auxiliary_options == nullptr)
    {
        return;
    }
    auto imgui_init_el = auxiliary_options->find(PRESENTS_OF_AUXILIARY_OPTIONS ::IMGUI);
    if (imgui_init_el == auxiliary_options->end())
    {
        return;
    }
    auto& imgui_init = imgui_init_el->second;
    if (imgui_init.type() != typeid(bool))
    {
        CALLISTO_THROW_EXCEPTION(c_f::argument_exception()) << c_f::build_error_tag_message(
            "Invalid type for field \'",
            PRESENTS_OF_AUXILIARY_OPTIONS::IMGUI,
            "\': ",
            imgui_init.type().name(),
            "."
        );
    }

    options.imgui = std::any_cast<bool>(imgui_init);
}
} // namespace

#pragma endregion

#pragma region construct_and_destruct

gl_monitor_context::gl_monitor_context(GLFWmonitor* monitor_handler)
{
    const GLFWvidmode* mode        = glfwGetVideoMode(monitor_handler);
    int                real_width  = 0;
    int                real_height = 0;
    glfwGetMonitorPhysicalSize(monitor_handler, &real_width, &real_height);

    __monitor_handler  = monitor_handler;
    __size.width       = mode->width;
    __size.height      = mode->height;
    __real_size.width  = real_width;
    __real_size.height = real_height;
    __dpi = static_cast<float>(__size.width) / (static_cast<float>(real_height) / 25.4F);
}

gl_monitor_context::~gl_monitor_context() {}

#pragma endregion

#pragma region implement_i_monitor_context

callisto::math::size2i gl_monitor_context::size() const { return __size; }

callisto::math::size2i gl_monitor_context::real_size() const { return __real_size; }

float gl_monitor_context::dpi() const { return __dpi; }

std::unique_ptr<i_window_context> gl_monitor_context::create_window(
    window_options                                  options,
    std::unordered_map<std::string_view, std::any>* auxiliary_options
)
{
    gl_window_options gl_win_options;

    check_and_get_auxiliary_options(auxiliary_options, gl_win_options);

    auto win_ptr = std::unique_ptr<i_window_context>();
    win_ptr.reset(new gl_window_context(__monitor_handler, options, gl_win_options));

    return win_ptr;
}

} // namespace callisto::graphics