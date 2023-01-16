// parent header
#include <callisto/graphics/a_window_processor.hpp>

namespace terramagnia::graphics
{

a_window_processor::~a_window_processor() { }

void a_window_processor::on_key_event(t_inp::key_event data) { }

void a_window_processor::on_mouse_button_event(t_inp::mouse_button_event data) { }

void a_window_processor::on_cursor_event(t_inp::cursor_event data) { }

void a_window_processor::on_change_position(c_m::point2i position) { }

void a_window_processor::on_resize(c_m::size2i size) { }

}