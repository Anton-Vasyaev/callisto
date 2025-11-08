#pragma once

// project
#include <callisto/framework/types/lifetime.hpp>

#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

#include <callisto/graphics/visual/i_monitor_context.hpp>
#include <callisto/graphics/visual/data/window_options.hpp>

namespace callisto::graphics
{

class gl_main_context;

class gl_monitor_context : public i_monitor_context
{
    friend class gl_main_context;

private:
    // data
    GLFWmonitor* __monitor_handler;

    std::int32_t __monitor_index;

    gl_main_context* __main_context;

    callisto::math::size2i __size;

    callisto::math::size2i __physical_size;

    callisto::math::size2f __content_scale;

    callisto::math::rectangle_i __work_area;

    const char* __name;

    float __dpi;

    // construct and destruct
    explicit gl_monitor_context(
        GLFWmonitor*     monitor_handler,
        std::int32_t     monitor_index,
        gl_main_context* main_context
    );

public:
    // construct and destruct
    gl_monitor_context() = delete;

    ~gl_monitor_context() override;

    CALLISTO_LIFETIME_REFERENCE(gl_monitor_context);

    // getters and setters
    GLFWmonitor* get_handler() { return __monitor_handler; }

    // implement i_monitor_context

    const char* get_name() const override;

    callisto::math::size2i get_size() const override;

    callisto::math::size2i get_physical_size() const override;

    callisto::math::size2f get_content_scale() const override;

    callisto::math::rectangle_i get_work_area() const override;

    float dpi() const override;

    // static methods
    static gl_monitor_context* validate_and_cast_ptr(i_monitor_context* monitor_context);
};

} // namespace callisto::graphics