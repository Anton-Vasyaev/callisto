// test
#include <callisto/framework/exception.hpp>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/string.hpp>

namespace c_f = callisto::framework;

TEST(framework_exception, exception)
{
    std::string exception_message;
    try
    {
        throw c_f::runtime_exception() << c_f::error_tag_message("Hello");
    }
    catch (const boost::exception& e)
    {
        exception_message = *boost::get_error_info<c_f::error_tag_message>(e);
    }

    ASSERT_EQ(exception_message, "Hello");
}