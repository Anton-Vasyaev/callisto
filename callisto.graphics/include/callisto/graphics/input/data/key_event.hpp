#pragma once

// project
#include "enum/input_action.hpp"
#include "enum/key_type.hpp"

namespace callisto::graphics
{

struct key_event
{
    key_type key;

    int32_t scan_code;

    input_action action;
};

}