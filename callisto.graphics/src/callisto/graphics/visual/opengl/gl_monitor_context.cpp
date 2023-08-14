#pragma once

// parent header
#include <callisto/graphics/visual/opengl/gl_monitor_context.hpp>
// std
#include <iostream>
// project
#include <callisto/framework/exception.hpp>

namespace callisto::graphics
{

#pragma region construct_and_destruct

gl_monitor_context::gl_monitor_context(GLFWmonitor* monitor_handler)
{
    const GLFWvidmode* mode       = glfwGetVideoMode(monitor_handler);
    int                real_width = 0, real_height = 0;
    glfwGetMonitorPhysicalSize(monitor_handler, &real_width, &real_height);

    this->monitor_handler   = monitor_handler;
    this->_size.width       = mode->width;
    this->_size.height      = mode->height;
    this->_real_size.width  = real_width;
    this->_real_size.height = real_height;
    this->_dpi              = _size.width / (real_height / 25.4f);
}

gl_monitor_context::~gl_monitor_context() {}

#pragma endregion

#pragma region implement_i_monitor_context

c_m::size2i gl_monitor_context::size() const { return this->_size; }

c_m::size2i gl_monitor_context::real_size() const { return this->_real_size; }

float gl_monitor_context::dpi() const { return this->_dpi; }

std::unique_ptr<i_window_context> gl_monitor_context::create_window(window_options options)
{
    auto window_position = options.area.position;
    auto window_size     = options.area.size;

    auto window_context = std::unique_ptr<i_window_context>();
    window_context.reset(new gl_window_context());

    auto window_handler = (GLFWwindow*)nullptr;

    auto validate_glfw_window_nullptr = [](GLFWwindow* window_handler)
    {
        if (window_handler == nullptr) throw std::runtime_error("cannot create glfw window");
    };

    if (options.mode == window_mode::fullscreen)
    {
        window_handler = glfwCreateWindow(
            window_size.width,
            window_size.height,
            "",
            this->monitor_handler,
            nullptr
        );
        validate_glfw_window_nullptr(window_handler);
    }
    else if (options.mode == window_mode::borderless)
    {
        int value = 0;
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        window_handler
            = glfwCreateWindow(window_size.width, window_size.height, "", nullptr, nullptr);
        glfwDefaultWindowHints();
    }
    else if (options.mode == window_mode::windowed)
    {
        window_handler
            = glfwCreateWindow(window_size.width, window_size.height, "", nullptr, nullptr);
        validate_glfw_window_nullptr(window_handler);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    glfwSetWindowPos(window_handler, window_position.x, window_position.y);

    auto window_ptr = reinterpret_cast<gl_window_context*>(window_context.get());

    window_ptr->options                = options;
    window_ptr->window_handler         = window_handler;
    window_ptr->parent_monitor_handler = this->monitor_handler;

    return window_context;
}

} // namespace callisto::graphics