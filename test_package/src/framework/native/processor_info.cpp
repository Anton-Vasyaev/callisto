// test
#include <callisto/framework/native/processor_info.hpp>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

// clang-format off

#define log_line_processor_info_property(property_name)                                             \
    c_f::gtest_console::print_line(                                                                 \
        "[processor_info] ", #property_name, ":",                                                   \
        c_f::processor_info::get_##property_name()                                                  \
    );

// clang-format on

TEST(framework_native, processor_info_placeholder_test_1)
{
    log_line_processor_info_property(vendor_name);
    log_line_processor_info_property(code_name);
    log_line_processor_info_property(brand_name);
    log_line_processor_info_property(num_cores);
    log_line_processor_info_property(num_logical_cpus);
    log_line_processor_info_property(total_logical_cpus);
    log_line_processor_info_property(l1_data_cache);
    log_line_processor_info_property(l1_instruction_cache);
    log_line_processor_info_property(l2_cache);
    log_line_processor_info_property(l3_cache);
    log_line_processor_info_property(l4_cache);
    log_line_processor_info_property(l1_assoc);
    log_line_processor_info_property(l1_data_assoc);
    log_line_processor_info_property(l1_instruction_assoc);
    log_line_processor_info_property(l2_assoc);
    log_line_processor_info_property(l3_assoc);
    log_line_processor_info_property(l4_assoc);
    log_line_processor_info_property(l1_cacheline);
    log_line_processor_info_property(l1_data_cacheline);
    log_line_processor_info_property(l1_instruction_cacheline);
    log_line_processor_info_property(l2_cacheline);
    log_line_processor_info_property(l3_cacheline);
    log_line_processor_info_property(l4_cacheline);

    ASSERT_EQ(true, true);
}