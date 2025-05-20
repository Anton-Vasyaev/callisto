// parent header
#include <callisto/graphics/visual/opengl/gl_main_context.hpp>
// std
#include <iostream>
#include <thread>
// project
#include <callisto/framework/exception.hpp>
#include <callisto/framework/string/build_string.hpp>

#include <callisto/graphics/visual/opengl/data/gl_window_options.hpp>

#include <callisto/graphics/visual/opengl/gl_window_context.hpp>

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

void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error, code:" << error << ", description:" << description << "\n";
}

void gl_main_context::__init_monitors()
{
    int           count            = 0;
    GLFWmonitor** monitor_handlers = glfwGetMonitors(&count);

    auto* primary_monitor_handler = glfwGetPrimaryMonitor();

    __monitors.reserve(count);
    for (int i = 0; i < count; i++)
    {
        if (monitor_handlers[i] == primary_monitor_handler)
        {
            __primary_monitor_index = i;
        }
        __monitors.push_back(std::unique_ptr<gl_monitor_context>(
            new gl_monitor_context(monitor_handlers[i], i, this)
        ));
    }
}

void gl_main_context::__glfw_monitor_callback(GLFWmonitor* monitor, int event)
{
    std::cout << "disconnect monitor:" << monitor << ", thread id:" << std::this_thread::get_id()
              << ", event:" << event << ".\n";
}

#pragma region construct_and_destruct

gl_main_context::gl_main_context()
{
    glfwSetErrorCallback(glfw_error_callback);
    const int glfw_status = glfwInit();
    if (glfw_status != GLFW_TRUE)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
            << c_f::error_tag_message("GLFW: failed to initialization");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(
        GLFW_OPENGL_FORWARD_COMPAT,
        GL_TRUE
    ); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    __init_monitors();

    glfwSetMonitorCallback(gl_main_context::__glfw_monitor_callback);
}

gl_main_context::~gl_main_context() { glfwTerminate(); }

#pragma endregion

#pragma region implement_i_main_context

std::int32_t gl_main_context::get_monitors_count()
{
    return static_cast<std::int32_t>(__monitors.size());
}

std::int32_t gl_main_context::get_primary_monitor_index()
{
    return static_cast<std::int32_t>(__primary_monitor_index);
}

i_monitor_context& gl_main_context::get_monitor_by_index(std::int32_t index)
{
    return *__monitors[index];
}

i_monitor_context& gl_main_context::get_primary_monitor()
{
    return *(__monitors[__primary_monitor_index]);
}

std::unique_ptr<i_window_context> gl_main_context::create_window(
    window_options                                  options,
    std::unordered_map<std::string_view, std::any>* auxiliary_options,
    i_monitor_context*                              monitor_context
)
{
    gl_monitor_context* gl_monitor_context_ptr = nullptr;
    if (monitor_context != nullptr)
    {
        gl_monitor_context_ptr = gl_monitor_context::validate_and_cast_ptr(monitor_context);
    }

    gl_window_options gl_win_options;

    check_and_get_auxiliary_options(auxiliary_options, gl_win_options);

    std::unique_ptr<i_window_context> window_ptr;
    window_ptr.reset(new gl_window_context(options, gl_win_options, gl_monitor_context_ptr));

    return window_ptr;
}

#pragma endregion

#pragma region getters_and_setters

std::vector<std::unique_ptr<gl_monitor_context>>& gl_main_context::get_glfw_monitors()
{
    return __monitors;
}

#pragma endregion

} // namespace callisto::graphics