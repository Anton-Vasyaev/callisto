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
    c_m::value_clamper<float> a(5.0F, -2.0F, 10.0F);

    a += 3.0F;
    a += 5.0F;
    a -= 15.3F;
    a *= 30.0F;
    a += 2.3F;
    a += 5.4F;

    ASSERT_TRUE(c_m::relative_error(a.value(), 1e-6F) == 5.7F);
}

TEST(math_utility, value_looper_test)
{
    c_m::value_looper<float> a(5.0F, -15.0F, 15.0F);

    a += 11.0F; // -14.0
    a *= 2.0F;  // 2.0;
    a += 37.0F; // 9.0;
    a -= 30.0F; // 9.0;
    a /= 4.5F;  // 2.0;

    ASSERT_TRUE(c_m::relative_error(a.value(), 1e-6F) == 2.0F);

    a = c_m::value_looper<float>(10.0, 5.0, 11.9);
    a /= 100.0F;

    ASSERT_TRUE(c_m::relative_error(a.value(), 1e-6F) == 7.0F);
}