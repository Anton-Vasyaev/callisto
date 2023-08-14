// parent header
#include <callisto/graphics/visual/a_window_processor.hpp>

namespace callisto::graphics
{

a_window_processor::~a_window_processor() {}

void a_window_processor::on_key_event(key_event data) {}

void a_window_processor::on_mouse_button_event(mouse_button_event data) {}

void a_window_processor::on_cursor_event(cursor_event data) {}

void a_window_processor::on_change_position(c_m::point2i position) {}

void a_window_processor::on_resize(c_m::size2i size) {}

} // namespace callisto::graphics