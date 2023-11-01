#pragma once

// 3rd party
#include <boost/exception/all.hpp>
#include <boost/exception/exception.hpp>
#include <boost/stacktrace.hpp>
// project
#include "common_tags.hpp"

#include <callisto/framework/app/application_environment.hpp>

namespace callisto::framework
{

struct stacktrace_error_tag_provider
{
    bool stacktrace_flag;
};

struct throw_utils
{
    static bool exception_trace_flag;

    inline static stacktrace_error_tag_provider error_tag_trace()
    {
        return stacktrace_error_tag_provider { application_environment::exception_trace_flag };
    }
};

// clang-format off

#define CALLISTO_THROW_EXCEPTION(exc_ob)                                            \
    throw exc_ob                                                                    \
        << callisto::framework::error_tag_function_name(BOOST_CURRENT_FUNCTION)     \
        << callisto::framework::error_tag_file_name(__FILE__)                       \
        << callisto::framework::error_tag_line(__LINE__)                            \
        << callisto::framework::throw_utils::error_tag_trace()

// clang-format on

template<class E>
inline
    typename boost::enable_if<boost::exception_detail::derives_boost_exception<E>, E const&>::type
    operator<<(E const& x, stacktrace_error_tag_provider&& p)
{
    if (p.stacktrace_flag)
    {
        return boost::exception_detail::set_info(
            x,
            error_tag_trace(boost::stacktrace::stacktrace())
        );
    }
    return x;
}

} // namespace callisto::framework