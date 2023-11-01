#pragma once

// project
#include "enum/mouse_button.hpp"
#include "enum/input_action.hpp"

namespace callisto::graphics
{

struct mouse_button_event
{
    mouse_button button;

    input_action action;
};

}