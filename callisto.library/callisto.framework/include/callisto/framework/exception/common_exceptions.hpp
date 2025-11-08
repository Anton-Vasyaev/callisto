#pragma once

// std
#include <exception>
// 3rd party
#include "exception.hpp"

namespace callisto::framework
{

/// @brief Presents exception during runtime.
struct runtime_exception : public virtual exception
{
};

/// @brief Presents argument checking exception.
struct argument_exception : public virtual exception
{
};

/// @brief Presents not find resources exception.
struct not_find_exception : public virtual exception
{
};

/// @brief Presents not enough resources to allocation.
struct bad_alloc_exception : public virtual exception
{
};

/// @brief Presents situation when method, function or part of functionality is not implemented.
struct not_implemented_exception : public virtual exception
{
};

} // namespace callisto::framework