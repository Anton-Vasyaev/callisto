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

class i_window_context
{
public:
    // handlers
    virtual callisto::framework::signal<void(key_event)>& get_key_event_signal() = 0;

    virtual callisto::framework::signal<void(mouse_button_event)>& get_mouse_button_event_signal()
        = 0;

    virtual callisto::framework::signal<void(cursor_event)>& get_cursor_event_signal() = 0;

    virtual callisto::framework::signal<void(callisto::math::point2i)>& get_change_position_signal()
        = 0;

    virtual callisto::framework::signal<void(callisto::math::size2i)>& get_resize_signal() = 0;

    virtual callisto::framework::signal<void(i_window_context&)>& get_processing_signal() = 0;

    // construct and destruct
    virtual ~i_window_context() = default;

    // methods
    virtual callisto::math::rectangle_i get_area() const = 0;

    virtual callisto::math::size2i get_viewport() const = 0;

    virtual window_mode get_window_mode() const = 0;

    virtual void set_processor(std::shared_ptr<a_window_processor> processor) = 0;

    virtual void start_processing() = 0;

    virtual void stop_processing() = 0;
};

} // namespace callisto::graphics