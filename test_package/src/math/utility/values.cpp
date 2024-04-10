// test
#include <callisto/math/utility/value_clamper.hpp>
#include <callisto/math/utility/value_looper.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>
#include <callisto/math/error.hpp>

namespace c_f = callisto::framework;
namespace c_m = callisto::math;

void test_func(float a) { c_f::gtest_console::print_line("float val:", a); }

TEST(math_utility, value_clamper_test)
{
    c_m::value_clamper<float> a(5.0, -2.0, 10.0);

    a += 3.0;
    a += 5.0;
    a -= 15.3;
    a *= 30.0;
    a += 2.3;
    a += 5.4;

    ASSERT_TRUE(c_m::relative_error(a.value(), 1e-6) == 5.7);
}

TEST(math_utility, value_looper_test)
{
    c_m::value_looper<float> a(5.0, -15.0, 15.0);

    a += 11.0; // -14.0
    a *= 2.0;  // 2.0;
    a += 37.0; // 9.0;
    a -= 30.0; // 9.0;
    a /= 4.5;  // 2.0;

    ASSERT_TRUE(c_m::relative_error(a.value(), 1e-6) == 2.0);

    a = c_m::value_looper<float>(10.0, 5.0, 11.9);
    a /= 100.0;

    ASSERT_TRUE(c_m::relative_error(a.value(), 1e-6) == 7.0);
}