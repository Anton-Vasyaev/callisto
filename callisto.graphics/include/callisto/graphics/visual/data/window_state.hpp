#pragma once

// project
#include <callisto/math/primitives.hpp>


namespace callisto::graphics
{

namespace
{
    namespace c_m = callisto::math;
}


struct window_state
{
    c_m::size2i viewport;
};

}