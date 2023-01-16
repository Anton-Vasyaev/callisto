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
    std::vector<std::unique_ptr<i_monitor_context>> monitors;

    std::unique_ptr<i_monitor_context> primary_monitor;

    // initialize methods
    void init_monitors();

    void init_primary_monitor();

public:
    // construct and destruct
    gl_main_context();

    virtual ~gl_main_context();

    // deleted
    gl_main_context(const gl_main_context&) = delete;

    gl_main_context(gl_main_context&& mainContext) = delete;

    gl_main_context& operator=(const gl_main_context&) = delete;

    gl_main_context& operator=(gl_main_context&&) = delete;

    // implement i_main_context
    virtual const std::vector<std::unique_ptr<i_monitor_context>>& get_monitors() override;

    virtual i_monitor_context& get_primary_monitor() override;
};

} // namespace callisto::graphics