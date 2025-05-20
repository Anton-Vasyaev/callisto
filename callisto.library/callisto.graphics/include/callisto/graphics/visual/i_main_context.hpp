#pragma once

// std
#include <vector>
// project
#include "i_monitor_context.hpp"
#include "i_window_context.hpp"

namespace callisto::graphics
{

class i_main_context
{
public:
    virtual ~i_main_context() = default;

    virtual std::int32_t get_monitors_count() = 0;

    virtual std::int32_t get_primary_monitor_index() = 0;

    virtual i_monitor_context& get_monitor_by_index(std::int32_t index) = 0;

    virtual i_monitor_context& get_primary_monitor() = 0;

    virtual std::unique_ptr<i_window_context> create_window(
        window_options                                  options,
        std::unordered_map<std::string_view, std::any>* auxiliary_options = nullptr,
        i_monitor_context*                              monitor_context   = nullptr
    ) = 0;
};

} // namespace callisto::graphics