#pragma once

// project
#include <callisto/math/primitives.hpp>
#include <callisto/graphics/input/data.hpp>

namespace callisto::graphics
{

class i_window_context;

class a_window_processor
{
public:
    a_window_processor() = default;

    virtual ~a_window_processor() = default;

    virtual void init(i_window_context& context) = 0;

    virtual void process(i_window_context& context) = 0;

    virtual void on_key_event(key_event data);

    virtual void on_mouse_button_event(mouse_button_event data);

    virtual void on_cursor_event(cursor_event data);

    virtual void on_change_position(const callisto::math::point2i& position);

    virtual void on_resize(const callisto::math::size2i& size);
};

} // namespace callisto::graphics