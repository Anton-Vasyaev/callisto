#pragma once

// std
#include <cstdint>

namespace callisto::graphics
{

struct font_symbol_metrics
{
    int32_t hori_bearing_x;
    int32_t hori_bearing_y;
    int32_t hori_advance;

    int32_t vert_bearing_x;
    int32_t vert_bearing_y;
    int32_t vert_advance;
};

} // namespace callisto::graphics