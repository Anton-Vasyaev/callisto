#pragma once

// std
#include <exception>
// project
#include "exception.hpp"

namespace callisto::framework
{

/// @brief Present base exception.
struct panic_exception : virtual std::exception, virtual boost::exception
{
    panic_exception() {}
};

} // namespace callisto::framework