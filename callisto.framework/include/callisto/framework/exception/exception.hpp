#pragma once

// std
#include <exception>
// 3rd party
#include <boost/exception/all.hpp>

namespace callisto::framework
{

/// @brief Present base exception.
struct exception : virtual std::exception, virtual boost::exception
{
};

} // namespace callisto::framework