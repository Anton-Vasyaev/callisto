#pragma once

// project macros
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>
// std
#include <thread>
#include <mutex>
#include <unordered_map>
#include <stdexcept>
// project
#include "gl_monitor_context.hpp"

#include <callisto/graphics/visual/i_window_context.hpp>

#include "data/gl_window_options.hpp"

namespace callisto::graphics
{

class gl_monitor_context;

class gl_main_context;

class gl_window_context : public i_window_context
{
    friend class gl_main_context;

private:
    // handlers
    callisto::framework::signal<void(key_event)> __key_event_signal_handler;

    callisto::framework::signal<void(mouse_button_event)> __mouse_button_event_signal_handler;

    callisto::framework::signal<void(cursor_event)> __cursor_event_signal_handler;

    callisto::framework::signal<void(callisto::math::point2i)> __change_position_signal_handler;

    callisto::framework::signal<void(callisto::math::size2i)> __resize_signal_handler;

    callisto::framework::signal<void(i_window_context&)> __processing_signal_handler;

    std::shared_ptr<a_window_processor> __window_processor;

    gl_main_context& __main_context;
    // data
    GLFWwindow* __window_handler = nullptr; // GLFW context

    gl_monitor_context* __monitor = nullptr;

    bool __processing_flag; // processing status

    window_options __win_options; // window properties

    gl_window_options __gl_win_options; // window properties for opengl

    callisto::math::size2i __viewport_value;

    bool __imgui_for_glfw_init_status = false;

    bool __imgui_for_gl_init_status = false;

    // static callbacks
    static void
    __context_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void __context_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    static void
    __context_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    static void __change_position_callback(GLFWwindow* window, int x_pos, int y_pos);

    static void __resize_callback(GLFWwindow* window, int width, int height);

    static void __context_framebuffer_size_callback(GLFWwindow* window, int width, int height);

    // processing
    void __processing();

    void __key_processing(int key, int scancode, int action, int mods);

    void __cursor_position_processing(double xpos, double ypos);

    void __mouse_button_processing(int button, int action, int mods);

    void __position_processing(int x_pos, int y_pos);

    void __resize_processing(int width, int height);

    // construct and destruct
    gl_window_context(
        gl_main_context&         main_context,
        const window_options&    win_options,
        const gl_window_options& gl_win_options,
        gl_monitor_context*      monitor = nullptr
    );

public:
    ~gl_window_context() override;

    CALLISTO_LIFETIME_REFERENCE(gl_window_context);

    // interface signals
    callisto::framework::signal<void(key_event)>& get_key_event_signal() override;

    callisto::framework::signal<void(mouse_button_event)>& get_mouse_button_event_signal() override;

    callisto::framework::signal<void(cursor_event)>& get_cursor_event_signal() override;

    callisto::framework::signal<void(callisto::math::point2i)>&
    get_change_position_signal() override;

    callisto::framework::signal<void(callisto::math::size2i)>& get_resize_signal() override;

    callisto::framework::signal<void(i_window_context&)>& get_processing_signal() override;

    // interface methods
    callisto::math::rectangle_i get_area() const override;

    callisto::math::size2i get_viewport() const override;

    window_mode get_window_mode() const override;

    void set_processor(std::shared_ptr<a_window_processor> processor) override;

    void start_processing() override;

    void stop_processing() override;

    void reset_window_options(window_options win_options, i_monitor_context* monitor_ptr = nullptr)
        override;

    // getters and setters
    i_monitor_context* get_monitor();

    GLFWwindow* get_window_handler();

    gl_window_options get_gl_win_options() const;
};

} // namespace callisto::graphics
