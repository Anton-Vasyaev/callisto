#pragma once

namespace callisto::graphics
{

enum class input_action
{
    unknown,

    press,

    repeat,

    release
};

inline constexpr const char* input_action_str(input_action action) noexcept
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