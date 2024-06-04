#pragma once

// project
#include <callisto/graphics/visual/i_monitor_context.hpp>
#include <callisto/graphics/visual/data/window_options.hpp>
#include "gl_window_context.hpp"

namespace callisto::graphics
{

class gl_monitor_context : public i_monitor_context
{
    friend class gl_main_context;

private:
    // data
    GLFWmonitor* monitor_handler;

    callisto::math::size2i _size;

    callisto::math::size2i _real_size;

    float _dpi;

    // construct and destruct
    explicit gl_monitor_context(GLFWmonitor* monitor_handler);

public:
    ~gl_monitor_context() override;

    // deleted
    gl_monitor_context() = delete;

    gl_monitor_context(const gl_monitor_context&) = delete;

    gl_monitor_context(gl_monitor_context&&) = delete;

    gl_monitor_context& operator=(const gl_monitor_context&) = delete;

    gl_monitor_context& operator=(gl_monitor_context&&) = delete;

    // implement i_monitor_context
    callisto::math::size2i size() const override;

    callisto::math::size2i real_size() const override;

    float dpi() const override;

    std::unique_ptr<i_window_context> create_window(window_options options) override;
};

} // namespace callisto::graphics