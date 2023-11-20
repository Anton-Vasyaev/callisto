#pragma once

// std
#include "exception.hpp"
// 3rd party
#include <boost/current_function.hpp>
#include <boost/stacktrace.hpp>

namespace callisto::framework
{

/// @brief Present error tag with std::string message.
using error_tag_message = boost::error_info<struct tag_message, std::string>;

/// @brief Present error tag with std::wstring message.
using error_tag_message_w = boost::error_info<struct tag_message_w, std::wstring>;

/// @brief Present error tag with file name in which the exception is thrown.
using error_tag_file_name = boost::error_info<struct tag_file_name, std::string>;

/// @brief Present error tag witch stacktrace in wthich exception is thrown.
using error_tag_trace = boost::error_info<struct tag_trace, boost::stacktrace::stacktrace>;

/// @brief Present error tag with location in which the exception is thrown.
using error_tag_location = boost::error_info<struct tag_location, std::string>;

} // namespace callisto::framework