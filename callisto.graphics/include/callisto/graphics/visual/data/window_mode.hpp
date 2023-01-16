#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

namespace callisto::graphics
{
    
CALLISTO_DEFINE_OBJECT_ENUM(
    window_mode,
    ,
    (unknown),
    (fullscreen),
    (borderless),
    (windowed)
);

}