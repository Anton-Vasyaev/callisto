#pragma once

#include "exception.hpp"

namespace callisto::framework
{

/// @brief present exception for process/program exit logic.
struct exit_exception : virtual std::exception, virtual boost::exception
{
    exit_exception() = default;
};

} // namespace callisto::framework