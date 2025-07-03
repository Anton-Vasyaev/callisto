#pragma once

#include <callisto/framework/exception.hpp>

#include "data/enum/gl_error_type.hpp"

namespace callisto::graphics
{

class gl_operation_error_exception : public callisto::framework::exception
{
    const char* __function_name;

    gl_error_type __error_type;

public:
    gl_operation_error_exception(const char* function_name, gl_error_type error_type)
    {
        __function_name = function_name;
        __error_type    = error_type;
    }

    std::string form_error_message() const override;
};

// clang-format off

#define CALLISTO_GRAPHICS_WRAP_GL_OPERATION(function_name, ...)                 \
    {                                                                           \
        function_name(__VA_ARGS__);                                             \
        auto err_code = glGetError();                                           \
        if(err_code)                                                            \
        {                                                                       \
            auto err_type = gl_error_type_from_original(err_code);              \
                                                                                \
            CALLISTO_THROW_EXCEPTION( gl_operation_error_exception(             \
                #function_name,                                                 \
                err_type                                                        \
            ));                                                                 \
        }                                                                       \
    }

// clang-format on

} // namespace callisto::graphics