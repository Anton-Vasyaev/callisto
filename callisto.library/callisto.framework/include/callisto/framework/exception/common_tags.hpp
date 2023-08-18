#pragma once

// std
#include "exception.hpp"

namespace callisto::framework
{

/// @brief Present error tag with std::string message.
using error_tag_message = boost::error_info<struct tag_message, std::string>;

/// @brief Present error tag with std::wstring message.
using error_tag_message_w = boost::error_info<struct tag_message_w, std::wstring>;

/// @brief Present error tag with function name in which the exception is thrown.
using error_tag_function_name = boost::error_info<struct tag_function_name, std::string>;

} // namespace callisto::framework