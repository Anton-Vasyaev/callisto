// test
#include <callisto/framework/native/numeric_type.hpp>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

using nt = c_f::numeric_type;

#define PRINT_TYPE_INFO(type)                           \
    auto n_##type = c_f::numeric_type_instance<type>(); \
    c_f::gtest_console::print_line(                     \
        "c type:",                                      \
        #type,                                          \
        ", numeric_type str:",                          \
        c_f::numeric_type_str(n_##type),                \
        ", byte_size:",                                 \
        c_f::numeric_type_size(n_##type)                \
    );

TEST(framework_native, native_numeric_type_test)
{
    PRINT_TYPE_INFO(uint8_t);
    PRINT_TYPE_INFO(int8_t);
    PRINT_TYPE_INFO(uint16_t);
    PRINT_TYPE_INFO(int16_t);
    PRINT_TYPE_INFO(uint32_t);
    PRINT_TYPE_INFO(int32_t);
    PRINT_TYPE_INFO(uint64_t);
    PRINT_TYPE_INFO(int64_t);
    PRINT_TYPE_INFO(float32_t);
    PRINT_TYPE_INFO(float64_t);
}