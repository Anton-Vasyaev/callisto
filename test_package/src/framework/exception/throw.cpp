#ifndef CALLISTO_MATH_DISABLE

    // test
    #include <callisto/framework/exception.hpp>
    // 3rd party
    #include <gtest/gtest.h>
    // project
    #include <callisto/framework/test/gtest.hpp>
    #include <callisto/framework/string/build_string.hpp>

namespace c_f = callisto::framework;

template<typename code_type>
using error_tag_code = boost::error_info<struct tag_code, code_type>;

struct random_point_exception : public c_f::exception
{
    float x;
    float y;

    random_point_exception(float x, float y) : x(x), y(y) {}

    virtual std::string form_error_message() const
    {
        return c_f::_bs("Ivalid point coords: (", x, ", ", y, ").");
    }
};

enum class custom_error_code
{
    not_found,
    not_allocated,
    not_compiled
};

void call_exception_1() { CALLISTO_THROW_EXCEPTION(random_point_exception(5.0, 3.0)); }

void call_exception_2()
{
    CALLISTO_THROW_EXCEPTION(c_f::argument_exception())
        << c_f::error_tag_message(c_f::_bs("Number is ", 5))
        << error_tag_code<custom_error_code>(custom_error_code::not_compiled);
}

void foo_1() { call_exception_1(); }

void foo_2() { foo_1(); }

void foo_3() { foo_2(); }

void bar_1() { call_exception_2(); }

void bar_2() { bar_1(); }

void bar_3() { bar_2(); }

void exception_example()
{
    try
    {
        foo_3();
    }
    catch (boost::exception& e)
    {
        auto boost_d_i = boost::diagnostic_information(e);

        c_f::gtest_console::print_line("Catch boost exception:", boost_d_i);
    }

    try
    {
        bar_3();
    }
    catch (boost::exception& e)
    {
        auto boost_d_i = boost::diagnostic_information(e);

        c_f::gtest_console::print_line("Catch boost exception:", boost_d_i);

        auto error_code = boost::get_error_info<error_tag_code<custom_error_code>>(e);

        if (error_code == nullptr)
        {
            c_f::gtest_console::print_line("Not find error code");
        }
        else
        {
            c_f::gtest_console::print_line("Error code:", int(*error_code));
        }
    }
}

TEST(framework_app, throw_exception)
{
    c_f::gtest_console::print_line("callisto exception stacktrace disable-----");
    exception_example();

    c_f::application_environment::exception_trace_flag    = true;
    c_f::application_environment::exception_location_flag = true;

    c_f::gtest_console::print_line("callisto exception stacktrace enable-----");
    exception_example();
}

#endif