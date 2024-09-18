// test
#include <callisto/utility/random/randomizer.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
// project

namespace c_m = callisto::math;
namespace c_u = callisto::utility;

void test_next(c_u::randomizer& randomizer)
{
    for (auto i = 0; i < 100; i++)
    {
        auto val_d = randomizer.next();
        ASSERT_TRUE(0.0 <= val_d && val_d <= 1.0);

        auto val_f = randomizer.next<float>();
        ASSERT_TRUE(0.0 <= val_f && val_f <= 1.0);

        val_d = randomizer.next<double>();
        ASSERT_TRUE(0.0 <= val_d && val_d <= 1.0);
    }
}

template<typename value_type>
void test_range(c_u::randomizer& randomizer, c_m::range<value_type> range)
{
    for (auto i = 0; i < 100; i++)
    {
        auto val_f = randomizer.next_range<float>(range);
        ASSERT_TRUE(range.min <= val_f && val_f <= range.max);
        auto val_d = randomizer.next_range<double>(range);
        ASSERT_TRUE(range.min <= val_d && val_d <= range.max);

        val_f = randomizer.next_range<float>(range.min, range.max);
        ASSERT_TRUE(range.min <= val_f && val_f <= range.max);

        val_d = randomizer.next_range<double>(range.min, range.max);
        ASSERT_TRUE(range.min <= val_d && val_d <= range.max);
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

    test_int_range(randomizer, c_m::range_i(2, 3));
    test_int_range(randomizer, c_m::range_l(5, 10));
    test_int_range(randomizer, c_m::range<uint8_t>(5, 20));
    test_int_range(randomizer, c_m::range<int16_t>(-100, 100));

    /*
    auto rand   = randomizer.next();
    auto rand_f = randomizer.next<float>();

    auto rand_f_2 = randomizer.next_range<float>(0.5, 0.3);

    auto range_l = c_m::range_l(-10, 10);

    auto rand_f_3 = randomizer.next_range<float>(range_l);
    */
}