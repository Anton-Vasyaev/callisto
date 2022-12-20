// test
#include <callisto/framework/ios/sequence_printer.hpp>
// std
#include <list>
#include <sstream>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

TEST(framework_ios, sequence_printer_placeholder_test)
{
    auto seq = std::list<int> { 45, 54, 32, 61, 16, 7 };

    std::wstringstream ss;
    ss << "seq:" << c_f::sequence_printer(seq);

    c_f::gtest_console::wprint_line(ss.str());
}
