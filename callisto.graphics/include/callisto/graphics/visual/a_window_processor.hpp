#pragma once

// project
#include <callisto/math/primitives.hpp>
#include <callisto/graphics/input/data.hpp>


namespace terramagnia::graphics
{

namespace
{
    namespace c_f = callisto::framework;
    
    namespace c_m = callisto::math;
}


class i_window_context;

class a_window_processor
{
public:
    inline a_window_processor() {}

    virtual ~a_window_processor();

    virtual void init(i_window_context& context) = 0;

    virtual void process(i_window_context& context) = 0;

    virtual void on_key_event(key_event data);

    virtual void on_mouse_button_event(mouse_button_event data);

    virtual void on_cursor_event(cursor_event data);

    virtual void on_change_position(c_m::point2i position);

    virtual void on_resize(c_m::size2i size);
};

} // namespace terramagnia::graphics