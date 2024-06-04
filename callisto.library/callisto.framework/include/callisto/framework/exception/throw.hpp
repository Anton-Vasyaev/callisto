#pragma once

// 3rd party
#include <boost/exception/all.hpp>
#include <boost/exception/exception.hpp>
#include <boost/stacktrace.hpp>
// project
#include "common_tags.hpp"

#include <callisto/framework/app/application_environment.hpp>
#include <callisto/framework/string/build_string.hpp>

namespace callisto::framework
{

struct stacktrace_error_tag_provider
{
    bool stacktrace_flag;

    bool location_flag;

    const char* function_name;

    const char* file_name;

    int file_line;
};

struct throw_utils
{
    static bool exception_trace_flag;

    static stacktrace_error_tag_provider
    error_tag_trace(const char* function_name, const char* file_name, int file_line)
    {
        return stacktrace_error_tag_provider { application_environment::exception_trace_flag,
                                               application_environment::exception_location_flag,
                                               function_name,
                                               file_name,
                                               file_line };
    }
};

// clang-format off

#define CALLISTO_THROW_EXCEPTION(exc_ob)                                               \
                                                                                        \
        throw exc_ob                                                                  \
            << callisto::framework::throw_utils::error_tag_trace(                       \
                BOOST_CURRENT_FUNCTION,                                                 \
                __FILE__,                                                               \
                __LINE__                                                                \
            )

// clang-format on

// NOLINTBEGIN(modernize-use-constraints)
template<class exc_type>
inline typename boost::
    enable_if<boost::exception_detail::derives_boost_exception<exc_type>, const exc_type&>::type
    operator<<(const exc_type& exception_data, stacktrace_error_tag_provider&& provider)
{
    if (provider.stacktrace_flag)
    {
        boost::exception_detail::set_info(
            exception_data,
            error_tag_trace(boost::stacktrace::stacktrace())
        );
    }

    if (provider.location_flag)
    {
        auto location_str = _bs(
            "file:",
            provider.file_name,
            " [",
            provider.file_line,
            " line] :",
            provider.function_name
        );
        boost::exception_detail::set_info(
            exception_data,
            callisto::framework::error_tag_location(location_str)
        );
    }
    return exception_data;
}

// NOLINTEND(modernize-use-constraints)

} // namespace callisto::framework