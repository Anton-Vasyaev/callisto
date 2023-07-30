#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

namespace callisto::graphics
{

enum class input_action
{
    unknown,

    press,

    repeat,

    release
};

inline constexpr const char* input_action_str(input_action action)
{
    switch (action)
    {
        case input_action::press : return "press";
        case input_action::repeat : return "repeat";
        case input_action::release : return "release";

        default : return "unknown";
    }
}

} // namespace callisto::graphics