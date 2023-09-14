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

/// @brief Present error tage with number of line in which the exception is thrown.
using error_tag_line = boost::error_info<struct tag_line, int>;

/// @brief Present error tag with function name in which the exception is thrown.
using error_tag_function_name = boost::error_info<struct tag_function_name, std::string>;

/// @brief Present error tag witch stacktrace in wthich exception is thrown.
using error_tag_trace = boost::error_info<struct tag_trace, boost::stacktrace::stacktrace>;

} // namespace callisto::framework