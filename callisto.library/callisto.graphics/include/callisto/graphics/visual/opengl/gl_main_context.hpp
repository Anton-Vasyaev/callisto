#pragma once

// std
#include <stdexcept>
#include <vector>
#include <memory>
// project
#include <callisto/graphics/visual/i_main_context.hpp>
#include <callisto/graphics/visual/opengl/gl_monitor_context.hpp>

namespace callisto::graphics
{

class gl_main_context : public i_main_context
{
private:
    // data
    std::vector<std::unique_ptr<gl_monitor_context>> __monitors;

    std::int32_t __primary_monitor_index;

    // initialize methods
    void __init_monitors();

    static void __glfw_monitor_callback(GLFWmonitor* monitor, int event);

public:
    // construct and destruct
    gl_main_context();

    ~gl_main_context() override;

    // deleted
    gl_main_context(const gl_main_context&) = delete;

    gl_main_context(gl_main_context&& mainContext) = delete;

    gl_main_context& operator=(const gl_main_context&) = delete;

    gl_main_context& operator=(gl_main_context&&) = delete;

    // implement i_main_context
    std::int32_t get_monitors_count() override;

    std::int32_t get_primary_monitor_index() override;

    i_monitor_context& get_monitor_by_index(std::int32_t index) override;

    i_monitor_context& get_primary_monitor() override;

    std::unique_ptr<i_window_context> create_window(
        window_options                                  options,
        std::unordered_map<std::string_view, std::any>* auxiliary_options = nullptr,
        i_monitor_context*                              monitor_context   = nullptr
    ) override;

    // getters and setters
    std::vector<std::unique_ptr<gl_monitor_context>>& get_glfw_monitors();
};

} // namespace callisto::graphics