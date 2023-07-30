#pragma once

// std
#include <exception>
// project
#include "exception.hpp"

namespace callisto::framework
{

struct panic_exception : virtual ::exception
{
public:
    panic_exception() {}
};

} // namespace callisto::framework