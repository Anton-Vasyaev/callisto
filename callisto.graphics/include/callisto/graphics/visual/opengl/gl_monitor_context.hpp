#pragma once

// project
#include <callisto/graphics/visual/i_monitor_context.hpp>
#include <callisto/graphics/visual/data/window_options.hpp>
#include "gl_window_context.hpp"

namespace c_m = callisto::math;

namespace callisto::graphics
{

class gl_monitor_context : public i_monitor_context
{
    friend class gl_main_context;

private:
    // data
    GLFWmonitor* monitor_handler;

    c_m::size2i _size;

    c_m::size2i _real_size;

    float _dpi;

    // construct and destruct
    gl_monitor_context(GLFWmonitor* monitor_handler);

public:
    virtual ~gl_monitor_context();

    // deleted
    gl_monitor_context() = delete;

    gl_monitor_context(const gl_monitor_context&) = delete;

    gl_monitor_context(gl_monitor_context&&) = delete;

    gl_monitor_context& operator=(const gl_monitor_context&) = delete;

    gl_monitor_context& operator=(gl_monitor_context&&) = delete;

    // implement i_monitor_context
    virtual c_m::size2i size() const override;

    virtual c_m::size2i real_size() const override;

    virtual float dpi() const override;

    virtual std::unique_ptr<i_window_context> create_window(window_options options) override;
};

} // namespace callisto::graphics