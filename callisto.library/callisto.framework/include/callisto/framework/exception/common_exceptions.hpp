#pragma once

// std
#include <exception>
// 3rd party
#include "exception.hpp"

namespace callisto::framework
{

/// @brief Present exception during runtime.
struct runtime_exception : virtual exception
{
};

/// @brief Present argument checking exception.
struct argument_exception : virtual exception
{
};

} // namespace callisto::framework