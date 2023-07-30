#pragma once

// project
#include <callisto/graphics/input/data.hpp>
#include <callisto/graphics/visual/opengl/third_party/include_gl.hpp>

namespace callisto::graphics
{

struct input_types_auxiliary
{
    static input_action get_input_action_from_glfw(int code)
    {
        switch (code)
        {
            case GLFW_PRESS : return input_action::press;

            case GLFW_REPEAT : return input_action::repeat;

            case GLFW_RELEASE : return input_action::release;

            default : return input_action::unknown;
        }
    }
};

} // namespace callisto::graphics