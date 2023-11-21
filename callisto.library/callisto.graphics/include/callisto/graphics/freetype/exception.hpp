#pragma once

// std
#include <string>
// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// 3rd party
#include <boost/exception/all.hpp>
// project
#include <callisto/framework/string/build_string.hpp>
#include <callisto/framework/exception.hpp>

namespace c_f = callisto::framework;

namespace callisto::graphics::freetype
{

struct freetype_exception : public virtual c_f::exception
{
};

struct freetype_native_function_exception : public virtual freetype_exception
{
    FT_Error error_code;

    const char* function_name;

    freetype_native_function_exception(FT_Error error_code, const char* function_name) :
        error_code(error_code), function_name(function_name)
    {
    }

    virtual std::string form_error_message() const
    {
        return c_f::_bs(
            "error during call freetype native function \'",
            function_name,
            "\', FT_Error code:",
            error_code,
            "."
        );
    }
};

} // namespace callisto::graphics::freetype

// clang-format off

#define WRAP_CALL_FREETYPE_FUNC(func_name, ...)                                                 \
    if(auto error_code = func_name(__VA_ARGS__))                                                \
    {                                                                                           \
        CALLISTO_THROW_EXCEPTION(freetype_native_function_exception(error_code, #func_name));   \
    }

// clang-format on