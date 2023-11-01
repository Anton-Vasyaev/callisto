#pragma once

// std
#include <string>
// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// 3rd party
#include <boost/exception/all.hpp>

namespace c_f = callisto::framework;

namespace callisto::graphics::freetype
{

struct api_operation_exception : virtual std::exception, virtual boost::exception
{
};

using error_tag_error_code = boost::error_info<struct tag_error_code, FT_Error>;

using error_tag_api_function_name = boost::error_info<struct tag_api_function_name, const char*>;

} // namespace callisto::graphics::freetype

// clang-format off

#define WRAP_CALL_FREETYPE_FUNC(func_name, ...)                                           \
    if(auto error_code = func_name(__VA_ARGS__))                                          \
    {                                                                                     \
        throw callisto::graphics::freetype::api_operation_exception()                     \
            << callisto::graphics::freetype::error_tag_error_code(error_code)             \
            << callisto::graphics::freetype::error_tag_api_function_name(#func_name);     \
    }

// clang-format on