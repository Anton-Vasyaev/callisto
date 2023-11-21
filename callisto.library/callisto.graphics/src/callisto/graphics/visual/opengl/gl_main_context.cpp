// parent header
#include <callisto/graphics/visual/opengl/gl_main_context.hpp>
// std
#include <iostream>
// project
#include <callisto/framework/exception.hpp>
#include <callisto/framework/string/build_string.hpp>

namespace callisto::graphics
{

void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error, code:" << error << ", description:" << description << std::endl;
}

#pragma region initialize_methods

void gl_main_context::init_monitors()
{
    int           count            = 0;
    GLFWmonitor** monitor_handlers = glfwGetMonitors(&count);
    this->monitors.reserve(count);
    for (int i = 0; i < count; i++)
    {
        this->monitors.push_back(
            std::unique_ptr<i_monitor_context>(new gl_monitor_context(monitor_handlers[i]))
        );
    }
}

void gl_main_context::init_primary_monitor()
{
    auto primary_monitor_handler = glfwGetPrimaryMonitor();
    if (primary_monitor_handler == nullptr)
    {
        CALLISTO_THROW_EXCEPTION(c_f::runtime_exception())
            << c_f::error_tag_message("GLFW: failed to get primary moniitor");
    }

    this->primary_monitor
        = std::unique_ptr<i_monitor_context>(new gl_monitor_context(primary_monitor_handler));
}

#pragma endregion

#pragma region construct_and_destruct

gl_main_context::gl_main_context()
{
    glfwSetErrorCallback(glfw_error_callback);
    int glfw_status = glfwInit();
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

    init_primary_monitor();
    init_monitors();
}

gl_main_context::~gl_main_context() { glfwTerminate(); }

#pragma endregion

#pragma region implement_i_main_context

const std::vector<std::unique_ptr<i_monitor_context>>& gl_main_context::get_monitors()
{
    return this->monitors;
}

i_monitor_context& gl_main_context::get_primary_monitor() { return *(this->primary_monitor); }

#pragma endregion

} // namespace callisto::graphics