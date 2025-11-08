// test
#include <callisto/framework/types/lifetime.hpp>
// std
#include <iostream>
#include <vector>
#include <memory>
// project
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

class base_lifetime_class
{
protected:
    void __move_from(base_lifetime_class&& other)
    {
        c_f::gtest_console::print_line("[base class] __move_from");
    }

    void __destroy() { c_f::gtest_console::print_line("[base class] __destroy"); }

public:
    CALLISTO_LIFETIME_MOVE_VIRTUAL(base_lifetime_class);

public:
    base_lifetime_class() { c_f::gtest_console::print_line("[base class] constructor"); }
};

class inher_lifetime_class : public base_lifetime_class
{
protected:
    void __move_from(inher_lifetime_class&& other)
    {
        base_lifetime_class::__move_from(std::move(other));

        c_f::gtest_console::print_line("[inheritance] __move_from");
    }

    void __destroy() { c_f::gtest_console::print_line("[inheritance] __destroy"); }

public:
    CALLISTO_LIFETIME_MOVE_VIRTUAL(inher_lifetime_class);

    inher_lifetime_class() { c_f::gtest_console::print_line("[inheritance] construct"); }
};

const char* border_line_str
    = "----------------------------------------------------------------------------------------------------\n";

void print_border_line() { c_f::gtest_console::print_line(border_line_str); }

void example_virtual_destruct()
{
    print_border_line();
    c_f::gtest_console::print_line("-----example virtual destruct");

    std::vector<std::unique_ptr<base_lifetime_class>> vectors;

    auto vec = std::make_unique<base_lifetime_class>();

    vectors.push_back(std::move(vec));

    std::unique_ptr<base_lifetime_class> vec2;
    vec2.reset(new inher_lifetime_class());
    vectors.push_back(std::move(vec2));

    print_border_line();
}

void example_move_from()
{
    {
        print_border_line();
        c_f::gtest_console::print_line("-----move constructor");
        auto vec1 = inher_lifetime_class();
        auto vec2 = std::move(vec1);

        print_border_line();
    }

    {
        print_border_line();
        c_f::gtest_console::print_line("-----move operator");
        auto vec1 = inher_lifetime_class();
        auto vec2 = inher_lifetime_class();

        vec1 = std::move(vec2);

        print_border_line();
    }
}

TEST(framework_types, lifetime_placeholder_test)
{
    example_virtual_destruct();

    example_move_from();
}