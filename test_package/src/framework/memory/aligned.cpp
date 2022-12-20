// test
#include <callisto/framework/memory/aligned.hpp>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

TEST(framework_memory, placeholder_aligned_test_1)
{
    auto memory_ptr_float    = c_f::make_align_unique_memory<float>(1024, 1024);
    auto memory_ptr_uint8_t  = c_f::make_align_unique_memory<uint8_t>(1024, 1024);
    auto memory_ptr_uint16_t = c_f::make_align_unique_memory<uint16_t>(1024, 1024);
    auto memory_ptr_uint32_t = c_f::make_align_unique_memory<uint32_t>(1024, 1024);
    auto memory_ptr_uint64_t = c_f::make_align_unique_memory<uint64_t>(1024, 1024);

    c_f::gtest_console::print_line("aligned ptr float:   ", memory_ptr_float);
    c_f::gtest_console::print_line("aligned ptr uint8_t: ", (uint64_t*)(memory_ptr_uint8_t.get()));
    c_f::gtest_console::print_line("aligned ptr uint16_t:", memory_ptr_uint16_t);
    c_f::gtest_console::print_line("aligned ptr uint32_t:", memory_ptr_uint32_t);
    c_f::gtest_console::print_line("aligned ptr uint64_t:", memory_ptr_uint64_t);

    ASSERT_EQ(true, true);
}
