// test
#include <callisto/framework/utility/slice.hpp>
// std
#include <initializer_list>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

using gtc = c_f::gtest_console;

void print_slices(std::initializer_list<c_f::slice> slices)
{
    gtc::print_line("slices:");
    for (const auto& slc : slices) { gtc::print_line("\t(", slc.start(), ", ", slc.end(), ")"); }
    gtc::print_line();
}

TEST(framework_utility, utility_slice_placeholder_test_1)
{
    print_slices({ c_f::slice(5, 13), c_f::slice(10, 15) });
    print_slices({
        {10, 20},
        {30, 40},
        {60, 80}
    });
    print_slices({ 2, 33, 45 });
    ASSERT_EQ(true, true);
}
