#pragma once

#include <callisto/framework/exception.hpp>

namespace callisto::graphics
{
namespace
{
    namespace c_f = callisto::framework;
}

struct opengl_exception : virtual c_f::exception { };

}