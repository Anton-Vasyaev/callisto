#pragma once

#include <callisto/graphics/input/data.hpp>


namespace callisto::graphics
{

struct input_types_auxiliary
{
    static input_action get_input_action_from_glfw(int code)
    {
        switch(code)
        {
            case GLFW_PRESS: return t_inp::input_action::press;
            
            case GLFW_REPEAT: return t_inp::input_action::repeat;

            case GLFW_RELEASE: return t_inp::input_action::release;

            default: return t_inp::input_action::unknown;
        }
    }
};

}