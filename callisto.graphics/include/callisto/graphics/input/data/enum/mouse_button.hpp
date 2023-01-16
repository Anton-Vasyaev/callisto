#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>


namespace callisto::graphics
{
CALLISTO_DEFINE_OBJECT_ENUM(
    mouse_button,
    ,
    (uknown, -1),
    (left, 0),
    (right, 1),
    (middle, 2),
    (_4, 3),
    (_5, 4),
    (_6, 5),
    (_7, 6),
    (_8, 7)
);
}