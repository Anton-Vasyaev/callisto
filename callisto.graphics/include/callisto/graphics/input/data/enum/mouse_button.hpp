#pragma once

// project
#include <callisto/framework/configuration/object_enum.hpp>

namespace callisto::graphics
{

enum class mouse_button
{
    uknown = -1,
    left   = 0,
    right  = 1,
    middle = 2,
    _4     = 3,
    _5     = 4,
    _6     = 5,
    _7     = 6,
    _8     = 7
};

inline constexpr const char* mouse_button_str(mouse_button button)
{
    switch (button)
    {
        case mouse_button::left : return "left";
        case mouse_button::right : return "right";
        case mouse_button::middle : return "middle";
        case mouse_button::_4 : return "_4";
        case mouse_button::_5 : return "_5";
        case mouse_button::_6 : return "_6";
        case mouse_button::_7 : return "_7";
        case mouse_button::_8 : return "_8";

        default : return "unknown";
    }
}

} // namespace callisto::graphics