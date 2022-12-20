// test
#include <callisto/framework/types/enum.hpp>
// std
#include <tuple>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

using user_info = std::tuple<std::string, std::string, uint8_t>;

enum user_field
{
    name,
    email,
    age
};

TEST(framework_types, enum_utype_test)
{
    auto john_name  = "john";
    auto john_email = "jonny@soap.net";
    auto john_age   = (uint8_t)32;

    auto john_data = user_info { john_name, john_email, john_age };

    ASSERT_EQ(john_name, std::get<c_f::enum_utype(user_field::name)>(john_data));
    ASSERT_EQ(john_email, std::get<c_f::enum_utype(user_field::email)>(john_data));
    ASSERT_EQ(john_age, std::get<c_f::enum_utype(user_field::age)>(john_data));
}