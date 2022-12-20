// test
#include <callisto/framework/templates/signal.hpp>
// std
#include <sstream>
// 3rd party
#include <gtest/gtest.h>

namespace c_f = callisto::framework;


std::stringstream stream;

void print_func()
{
    stream << "[print_func]";
}

TEST(framework_templates, signal_test_1)
{
    c_f::signal<void()> signal;

    auto functor = std::function(
        []()
        {
            stream << "[print_functor]";
        }
    );
    auto functor_raii = std::function(
        []()
        {
            stream << "[print_functor_raii]";
        }
    );

    auto connection_func   = signal.connect(print_func);
    auto connection_lambda = signal.connect(
        []()
        {
            stream << "[print_lambda]";
        }
    );
    auto connection_functor = signal.connect(functor);

    signal();

    {
        auto connection_raii = signal.connect(functor_raii).to_raii();
        signal();
    }

    for(int i = 0; i < 3; i++)
    {
        auto connection = signal.connect(print_func);
    }

    connection_functor.disconnect();
    auto connection_lambda_2 = signal.connect(
        []()
        {
            stream << "[print_lambda_2]";
        }
    );

    signal();

    std::string expected_string = ""
        "[print_func][print_lambda][print_functor]"
        "[print_func][print_lambda][print_functor][print_functor_raii]"
        "[print_func][print_lambda][print_func][print_func][print_func][print_lambda_2]";
    
    auto stream_string = stream.str();

    ASSERT_EQ(expected_string, stream_string);
}

void additional_func(int& a, int& b)
{
    a += 1;
    b += 2;
}

TEST(framework_templates, signal_test_2)
{
    c_f::signal<void(int&, int&)> signal;

    auto functor = std::function(
        [](int& a, int& b)
        {
            a *= 5;
            b *= 6;
        }
    );

    signal.connect(additional_func);
    signal.connect(
        [](int& a, int& b)
        {
            a *= 3;
            b *= 4;
        }
    );
    signal.connect(functor);

    int a = 1, b = 2;

    signal(a, b);

    ASSERT_EQ(a, 30);
    ASSERT_EQ(b, 96);
}