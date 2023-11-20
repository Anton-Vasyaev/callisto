#pragma once

// std
#include <exception>
// 3rd party
#include "exception.hpp"

namespace callisto::framework
{

/// @brief Present exception during runtime.
struct runtime_exception : public virtual exception
{
};

/// @brief Present argument checking exception.
struct argument_exception : public virtual exception
{
};

/// @brief Present not find resources exception.
struct not_find_exception : public virtual exception
{
}

} // namespace callisto::framework