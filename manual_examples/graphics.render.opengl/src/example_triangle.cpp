// parent header
#include "examples.hpp"
// std
#include <mutex>
#include <thread>
// project
#include <callisto/graphics/visual.hpp>

#include "processors/simple_triangle_processor.hpp"

namespace c_f = callisto::framework;
namespace c_g = callisto::graphics;

std::mutex PRINT_MUTEX;

std::mutex INIT_MUTEX;

void print_key_callback(c_g::key_type key)
{
    {
        auto lock = std::lock_guard(PRINT_MUTEX);

        std::cout << std::this_thread::get_id() << ": print key callback:" << c_g::key_type_str(key)
                  << "\n";
    }
}

void example_triangle_process(const char* title_name)
{
    try
    {
        c_g::graphics_context context;

        auto  lock       = std::unique_lock(INIT_MUTEX);
        auto& gl_context = context.get_context("opengl");

        auto& primary_monitor = gl_context.get_primary_monitor();

        auto auxiliary_options     = std::unordered_map<std::string_view, std::any>();
        auxiliary_options["imgui"] = true;

        auto window_up = primary_monitor.create_window(
            c_g::window_options(200, 200, 800, 800, c_g::window_mode::windowed),
            &auxiliary_options
        );

        window_up->get_key_event_signal().connect([](c_g::key_event key_event)
                                                  { print_key_callback(key_event.key); });

        auto triangle_processor_sp = std::shared_ptr<c_g::a_window_processor>();
        triangle_processor_sp.reset(new simple_triangle_processor());
        window_up->set_processor(triangle_processor_sp);
        lock.release();

        window_up->start_processing();
    }
    catch (boost::exception& e)
    {
        std::cerr << boost::diagnostic_information(e);
    }
    catch (std::exception& exc)
    {
        std::cerr << "exception in thread:" << exc.what() << "\n";
    }
}

void example_triangle_thread()
{
    auto t1 = std::thread(example_triangle_process, "thread1");
    // auto t2 = std::thread(example_triangle_process, "thread1");

    t1.join();
    // t2.join();
}

void example_triangle() { example_triangle_thread(); }