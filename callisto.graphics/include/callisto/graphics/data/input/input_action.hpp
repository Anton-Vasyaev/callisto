#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

namespace callisto::graphics
{

// clang-format off

CALLISTO_DEFINE_OBJECT_ENUM(
    input_action,
    ,
    (unknown),
    (press),
    (repeat),
    (release)
);

// clang-format on

} // namespace callisto::graphics