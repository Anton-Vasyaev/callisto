#pragma once

namespace callisto::graphics
{
struct gl_window_options
{
    bool imgui = false;

    int gl_multisampling = 0;

    int canvas_multisampling = 0;
};
} // namespace callisto::graphics