#ifndef CALLISTO_MATH_DISABLE

    // test
    #include <callisto/framework/exception.hpp>
    // 3rd party
    #include <gtest/gtest.h>
    // project
    #include <callisto/framework/test/gtest.hpp>
    #include <callisto/framework/string/build_string.hpp>

namespace c_f = callisto::framework;

struct random_exception : public c_f::exception
{
};

void call_exception_1() { CALLISTO_THROW_EXCEPTION(random_exception()); }

void call_exception_2()
{
    CALLISTO_THROW_EXCEPTION(c_f::argument_exception())
        << c_f::error_tag_message(c_f::_bs("Number is ", 5));
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
    }
}

TEST(framework_app, throw_exception)
{
    c_f::gtest_console::print_line("callisto exception stacktrace disable-----");
    exception_example();

    c_f::application_environment::exception_trace_flag = true;

    c_f::gtest_console::print_line("callisto exception stacktrace enable-----");
    exception_example();
}

#endif