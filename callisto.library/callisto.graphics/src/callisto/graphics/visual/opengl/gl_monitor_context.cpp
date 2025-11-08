// parent header
#include <callisto/graphics/visual/opengl/gl_monitor_context.hpp>
// std
#include <iostream>
// project
#include <callisto/framework/exception.hpp>

#include <callisto/graphics/visual/opengl/gl_main_context.hpp>

namespace callisto::graphics
{
namespace c_f = callisto::framework;

#pragma endregion

#pragma region static_methods

#pragma endregion

#pragma region construct_and_destruct

gl_monitor_context::gl_monitor_context(
    GLFWmonitor*     monitor_handler,
    std::int32_t     monitor_index,
    gl_main_context* main_context
)
{
    __monitor_handler = monitor_handler;
    __monitor_index   = monitor_index;
    __main_context    = main_context;

    __name = glfwGetMonitorName(__monitor_handler);

    const GLFWvidmode* mode = glfwGetVideoMode(__monitor_handler);
    __size.width            = mode->width;
    __size.height           = mode->height;

    glfwGetMonitorPhysicalSize(__monitor_handler, &__physical_size.width, &__physical_size.height);

    __dpi = static_cast<float>(__size.width) / (static_cast<float>(__physical_size.width) / 25.4F);

    glfwGetMonitorWorkarea(
        __monitor_handler,
        &__work_area.x,
        &__work_area.y,
        &__work_area.width,
        &__work_area.height
    );
}

gl_monitor_context::~gl_monitor_context() {}

#pragma endregion

#pragma region implement_i_monitor_context

const char* gl_monitor_context::get_name() const { return __name; }

callisto::math::size2i gl_monitor_context::get_size() const { return __size; }

callisto::math::size2i gl_monitor_context::get_physical_size() const { return __physical_size; }

callisto::math::size2f gl_monitor_context::get_content_scale() const { return __content_scale; }

callisto::math::rectangle_i gl_monitor_context::get_work_area() const { return __work_area; }

float gl_monitor_context::dpi() const { return __dpi; }

#pragma endregion

#pragma region static_methods

gl_monitor_context* gl_monitor_context::validate_and_cast_ptr(i_monitor_context* monitor_context)
{

    try
    {
        return dynamic_cast<gl_monitor_context*>(monitor_context);
    }
    catch (const std::exception& e)
    {
        CALLISTO_THROW_EXCEPTION(c_f::argument_exception())
            << c_f::error_tag_message("monitor context is not from opengl (gl_monitor_context).");
    }
}

#pragma endregion

} // namespace callisto::graphics