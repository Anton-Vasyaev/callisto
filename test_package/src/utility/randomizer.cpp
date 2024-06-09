// test
#include <callisto/utility/random/randomizer.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
// project

namespace c_m = callisto::math;
namespace c_u = callisto::utility;

template<typename value_type>
void test_range(c_u::randomizer& randomizer, c_m::range<value_type> range)
{
    for (auto i = 0; i < 100; i++)
    {
        auto val = randomizer.next_range(range);
        ASSERT_TRUE(range.min <= val && val <= range.max);

        val = randomizer.next_range(range.min, range.max);
        ASSERT_TRUE(range.min <= val && val <= range.max);
    }
}

template<typename value_type>
void test_int_range(c_u::randomizer& randomizer, c_m::range<value_type> range)
{
    for (auto i = 0; i < 100; i++)
    {
        auto val = randomizer.next_int_range(range);
        ASSERT_TRUE(range.min <= val && val <= range.max);

        val = randomizer.next_int_range(range.min, range.max);
        ASSERT_TRUE(range.min <= val && val <= range.max);
    }
}

TEST(math_utility, randomizer_test)
{
    auto randomizer = c_u::randomizer(1024);

    test_range(randomizer, c_m::range_f(50.0, 5242.556));
    test_range(randomizer, c_m::range_d(1.0, 1.1));
    test_range(randomizer, c_m::range_f(-1000000.0, -5000.0));
    test_range(randomizer, c_m::range_l(-10, 10));
    test_range(randomizer, c_m::range_i(-30, 30));

    test_int_range(randomizer, c_m::range_l(2, 3));
    test_int_range(randomizer, c_m::range_l(5, 10));
    test_int_range(randomizer, c_m::range_l(-1024LL * 1024LL, -1024));
    test_int_range(randomizer, c_m::range_l(-100, 100));
}