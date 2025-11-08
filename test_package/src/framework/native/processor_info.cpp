// test
#include <callisto/framework/native/processor_info.hpp>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

// clang-format off

#define LOG_LINE_PROCESSOR_INFO_PROPERTY(property_name)                                             \
    c_f::gtest_console::print_line(                                                                 \
        "[processor_info] ", #property_name, ":",                                                   \
        c_f::processor_info::get_##property_name()                                                  \
    );

// clang-format on

TEST(framework_native, processor_info_placeholder_test_1)
{
    if (!c_f::processor_info::is_init())
    {
        c_f::gtest_console::print_line(
            "processor info cannot initialize:",
            c_f::processor_info::get_not_init_error_message()
        );
    }
    else
    {

        LOG_LINE_PROCESSOR_INFO_PROPERTY(vendor_name);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(code_name);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(brand_name);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(num_cores);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(num_logical_cpus);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(total_logical_cpus);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_data_cache);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_instruction_cache);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l2_cache);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l3_cache);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l4_cache);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_assoc);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_data_assoc);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_instruction_assoc);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l2_assoc);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l3_assoc);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l4_assoc);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_cacheline);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_data_cacheline);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l1_instruction_cacheline);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l2_cacheline);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l3_cacheline);
        LOG_LINE_PROCESSOR_INFO_PROPERTY(l4_cacheline);
    }

    ASSERT_EQ(true, true);
}