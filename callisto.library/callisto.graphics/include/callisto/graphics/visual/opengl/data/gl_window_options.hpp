#pragma once

// std
#include <string_view>

namespace callisto::graphics
{
struct gl_window_options
{
    struct PRESENTS
    {
        static constexpr std::string_view IMGUI = "imgui";

        static constexpr std::string_view GL_MULTISAMPLING = "gl_multisampling";

        static constexpr std::string_view CANVAS_MULTISAMPLING = "gl_canvas_multisampling";
    };

    bool imgui = false;

    int gl_multisampling = 0;

    // -1 meaning max available samples
    int canvas_multisampling = -1;
};
} // namespace callisto::graphics