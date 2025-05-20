#pragma once

// std
#include <memory>
#include <unordered_map>
#include <any>
// project
#include <callisto/math/primitives.hpp>

#include "data/window_options.hpp"

namespace callisto::graphics
{
class i_monitor_context
{
public:
    // construct and destruct
    virtual ~i_monitor_context() = default;

    // methods
    virtual const char* get_name() const = 0;

    virtual callisto::math::size2i get_size() const = 0;

    virtual callisto::math::size2i get_physical_size() const = 0;

    virtual callisto::math::size2f get_content_scale() const = 0;

    virtual callisto::math::rectangle_i get_work_area() const = 0;

    virtual float dpi() const = 0;
};

} // namespace callisto::graphics