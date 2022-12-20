// test
#include <callisto/framework/ios/table_printer.hpp>
// std
#include <list>
#include <sstream>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

TEST(framework_ios, table_printer_placeholder_test)
{
    auto r1 = c_f::wtable_printer_row(L"minus", L"cherepovets-vologda", L"mutant");
    auto r2 = c_f::wtable_printer_row(L"gagarin", L"ol", L"mz", L"mars-jupiter-saturn");

    auto table_printer = c_f::wtable_printer {
        r1,
        r2,
        {"mars", "sosiska", 512, "kaban", "pig", 15.14f, "city"}
    };

    table_printer.append_row(std::move(c_f::wtable_printer_row(L"adolf", 5, L"rudolf", 243, L"|%|"))
    );
    table_printer.append_row(std::move(c_f::wtable_printer_row()));
    table_printer.append_row(std::move(c_f::wtable_printer_row("jonny")));

    table_printer.append_row({ "maslo", "apple", 1023, 5.05, "ekaterinburg" });

    for (auto& line : table_printer.get_print_lines(4)) { c_f::gtest_console::wprint_line(line); }
}