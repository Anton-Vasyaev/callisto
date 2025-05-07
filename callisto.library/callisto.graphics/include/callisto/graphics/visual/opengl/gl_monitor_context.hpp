#pragma once

// project
#include <callisto/framework/types/lifetime.hpp>

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
    GLFWmonitor* __monitor_handler;

    callisto::math::size2i __size;

    callisto::math::size2i __real_size;

    float __dpi;

    // construct and destruct
    explicit gl_monitor_context(GLFWmonitor* monitor_handler);

public:
    // construct and destruct
    gl_monitor_context() = delete;

    ~gl_monitor_context() override;

    CALLISTO_LIFETIME_REFERENCE(gl_monitor_context);

    // implement i_monitor_context
    callisto::math::size2i size() const override;

    callisto::math::size2i real_size() const override;

    float dpi() const override;

    std::unique_ptr<i_window_context> create_window(
        window_options                                  options,
        std::unordered_map<std::string_view, std::any>* auxiliary_options = nullptr
    ) override;
};

} // namespace callisto::graphics