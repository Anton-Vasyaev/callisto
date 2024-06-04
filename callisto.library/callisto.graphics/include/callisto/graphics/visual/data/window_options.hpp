#pragma once

// project
#include <callisto/math/primitives.hpp>

#include "window_mode.hpp"

namespace callisto::graphics
{

struct window_options
{
    callisto::math::rectangle_i area;

    window_mode mode;

    window_options()
    {
        area = callisto::math::rectangle_i::empty();
        mode = window_mode::windowed;
    }

    window_options(int x, int y, int width, int height, window_mode mode)
    {
        area       = { x, y, width, height };
        this->mode = mode;
    }

    window_options(callisto::math::rectangle_i area, window_mode mode)
    {
        this->area = area;
        this->mode = mode;
    }
};

}; // namespace callisto::graphics