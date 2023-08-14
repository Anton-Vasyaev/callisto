#pragma once

// project
#include <callisto/math/primitives.hpp>

#include "window_mode.hpp"

namespace callisto::graphics
{

namespace
{
namespace c_m = callisto::math;
}

struct window_options
{
    c_m::rectangle_i area;

    window_mode mode;

    window_options()
    {
        this->area = c_m::rectangle_i::empty();
        this->mode = window_mode::windowed;
    }

    window_options(int x, int y, int width, int height, window_mode mode)
    {
        this->area = { x, y, width, height };
        this->mode = mode;
    }

    window_options(c_m::rectangle_i area, window_mode mode)
    {
        this->area = area;
        this->mode = mode;
    }
};

}; // namespace callisto::graphics