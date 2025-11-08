// test
#include <callisto/framework.hpp>
#include <callisto/math.hpp>
#include <callisto/opencv.hpp>
#include <callisto/graphics.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

TEST(callisto, include_test)
{
    c_f::gtest_console::print_line("include opencv");

    ASSERT_EQ(true, true);
}