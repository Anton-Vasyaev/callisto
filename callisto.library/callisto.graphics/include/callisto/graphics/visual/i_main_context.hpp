#pragma once

// std
#include <vector>
// project
#include "i_monitor_context.hpp"

namespace callisto::graphics
{

class i_main_context
{
public:
    virtual ~i_main_context() {}

    virtual const std::vector<std::unique_ptr<i_monitor_context>>& get_monitors() = 0;

    virtual i_monitor_context& get_primary_monitor() = 0;
};

} // namespace callisto::graphics