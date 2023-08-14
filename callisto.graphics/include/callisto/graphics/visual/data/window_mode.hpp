#pragma once

namespace callisto::graphics
{

enum class window_mode
{
    unknown,
    fullscreen,
    borderless,
    windowed
};

constexpr const char* window_mode_str(window_mode mode) noexcept
{
    switch (mode)
    {
        case window_mode::fullscreen : return "fullscreen";
        case window_mode::borderless : return "borderless";
        case window_mode::windowed : return "windowed";

        default : return "unknown";
    }
}

} // namespace callisto::graphics