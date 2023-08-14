#pragma once

// std
#include <memory>
// project
#include <callisto/framework/templates/signal.hpp>
#include <callisto/math/primitives.hpp>

#include <callisto/graphics/input/data.hpp>

#include "a_window_processor.hpp"
#include "data/window_options.hpp"
#include "data/window_state.hpp"

namespace callisto::graphics
{

namespace
{

namespace c_f = callisto::framework;

namespace c_m = callisto::math;

} // namespace

class i_window_context
{
public:
    // handlers
    virtual c_f::signal<void(key_event)>& key_event_signal() = 0;

    virtual c_f::signal<void(mouse_button_event)>& mouse_button_event_signal() = 0;

    virtual c_f::signal<void(cursor_event)>& cursor_event_signal() = 0;

    virtual c_f::signal<void(c_m::point2i)>& change_position_signal() = 0;

    virtual c_f::signal<void(c_m::size2i)>& resize_signal() = 0;

    virtual c_f::signal<void(i_window_context&)>& processing_signal() = 0;

    // construct and destruct
    virtual ~i_window_context() {};

    // methods
    virtual c_m::rectangle_i get_area() const = 0;

    virtual c_m::size2i get_viewport() const = 0;

    virtual window_mode get_window_mode() const = 0;

    virtual void set_processor(std::shared_ptr<a_window_processor> processor) = 0;

    virtual void start_processing() = 0;

    virtual void stop_processing() = 0;
};

} // namespace callisto::graphics