#pragma once

// std
#include <cstdint>

namespace callisto::graphics
{

struct font_symbol_metrics
{
    float hori_bearing_x;
    float hori_bearing_y;
    float hori_advance;

    float vert_bearing_x;
    float vert_bearing_y;
    float vert_advance;

    bool strong_pixel_render;
};

} // namespace callisto::graphics