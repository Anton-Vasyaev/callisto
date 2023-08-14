// parent header
#include "examples.hpp"
// project
#include <callisto/graphics/visual.hpp>

#include "processors/simple_triangle_processor.hpp"

namespace c_f = callisto::framework;
namespace c_g = callisto::graphics;

void example_triangle(int argc, char* argv[])
{
    c_g::graphics_context context;

    auto& gl_context = context.get_context("opengl");

    auto& primary_monitor = gl_context.get_primary_monitor();

    auto window_up = primary_monitor.create_window(
        c_g::window_options(200, 200, 800, 800, c_g::window_mode::windowed)
    );

    auto triangle_processor_sp = std::shared_ptr<c_g::a_window_processor>();
    triangle_processor_sp.reset(new simple_triangle_processor());
    window_up->set_processor(triangle_processor_sp);

    window_up->start_processing();
}