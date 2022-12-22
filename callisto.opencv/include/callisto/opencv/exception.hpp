#pragma once

// 3rd party
#include <boost/exception/all.hpp>
#include <exception>

namespace callisto::opencv
{

struct read_write_exception : virtual std::exception, virtual boost::exception {};

} // namespace callisto::opencv