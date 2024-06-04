#pragma once

// project macros
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>
// std
#include <thread>
#include <mutex>
#include <unordered_map>
#include <stdexcept>
// project
#include <callisto/graphics/visual/i_window_context.hpp>

namespace callisto::graphics
{

class gl_window_context : public i_window_context
{
    friend class gl_monitor_context;

private:
    // handlers
    callisto::framework::signal<void(key_event)> key_event_signal_handler;

    callisto::framework::signal<void(mouse_button_event)> mouse_button_event_signal_handler;

    callisto::framework::signal<void(cursor_event)> cursor_event_signal_handler;

    callisto::framework::signal<void(callisto::math::point2i)> change_position_signal_handler;

    callisto::framework::signal<void(callisto::math::size2i)> resize_signal_handler;

    callisto::framework::signal<void(i_window_context&)> processing_signal_handler;

    std::shared_ptr<a_window_processor> window_processor;

    // data
    static std::unordered_map<GLFWwindow*, gl_window_context*> call_functions; // link with glfw

    static std::mutex call_functions_mutex;

    GLFWwindow* window_handler = nullptr; // GLFW context

    GLFWmonitor* parent_monitor_handler = nullptr;

    bool processing_flag; // processing status

    window_options options; // window properties

    callisto::math::size2i viewport_value;

    // static callbacks
    static void
    context_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void context_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    static void context_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    static void change_position_callback(GLFWwindow* window, int x_pos, int y_pos);

    static void resize_callback(GLFWwindow* window, int width, int height);

    static void context_framebuffer_size_callback(GLFWwindow* window, int width, int height);

    // processing
    void processing();

    void key_processing(int key, int scancode, int action, int mods);

    void cursor_position_processing(double xpos, double ypos);

    void mouse_button_processing(int button, int action, int mods);

    void position_processing(int x_pos, int y_pos);

    void resize_processing(int width, int height);

    // construct and destruct
    gl_window_context() = default;

public:
    ~gl_window_context() override;

    // deleted
    gl_window_context(const gl_window_context&) = delete;

    gl_window_context(gl_window_context&&) = delete;

    gl_window_context& operator=(const gl_window_context&) = delete;

    gl_window_context& operator=(gl_window_context&&) = delete;

    // interface signals
    callisto::framework::signal<void(key_event)>& key_event_signal() override;

    callisto::framework::signal<void(mouse_button_event)>& mouse_button_event_signal() override;

    callisto::framework::signal<void(cursor_event)>& cursor_event_signal() override;

    callisto::framework::signal<void(callisto::math::point2i)>& change_position_signal() override;

    callisto::framework::signal<void(callisto::math::size2i)>& resize_signal() override;

    callisto::framework::signal<void(i_window_context&)>& processing_signal() override;

    // interface methods
    callisto::math::rectangle_i get_area() const override;

    callisto::math::size2i get_viewport() const override;

    window_mode get_window_mode() const override;

    void set_processor(std::shared_ptr<a_window_processor> processor) override;

    void start_processing() override;

    void stop_processing() override;

    // getters and setters
    inline GLFWwindow* get_window_handler() const;

    inline GLFWmonitor* get_monitor_handler() const;
};

// inline implementations

#pragma region getters_and_setters

inline GLFWwindow* gl_window_context::get_window_handler() const { return this->window_handler; }

inline GLFWmonitor* gl_window_context::get_monitor_handler() const
{
    return this->parent_monitor_handler;
}

#pragma endregion

} // namespace callisto::graphics
