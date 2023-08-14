#pragma once

// std
#include <memory>
// project
#include <callisto/math/primitives.hpp>

#include "data/window_options.hpp"
#include "i_window_context.hpp"

namespace callisto::graphics
{
namespace
{
namespace c_m = callisto::math;
}

class i_monitor_context
{
public:
    // construct and destruct
    virtual ~i_monitor_context() {}

    // methods
    virtual c_m::size2i size() const = 0;

    virtual c_m::size2i real_size() const = 0;

    virtual float dpi() const = 0;

    virtual std::unique_ptr<i_window_context> create_window(window_options options) = 0;
};

} // namespace callisto::graphics