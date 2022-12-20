#pragma once

// std
#include <iostream>
#include <sstream>
// project
#include <callisto/framework/types/ios_types.hpp>
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::framework
{

/// @brief Provide gtest-format printing information in console.
class gtest_console
{
public:
    /// @brief Basic tempalte function of gtest-format printing in console
    /// @tparam char_type Type of char.
    /// @tparam ...args_type Parameter pack type of variadic data.
    /// @param ...args Variadic data.
    template<typename char_type, typename... args_type>
    static void basic_print_line(const args_type&... args)
    {
        static_assert(is_any_v<char_type, char, wchar_t>, "char_type can only be char | wchar_t");
        auto& std_cout = ios_types<char_type>::std_cout();

        typename ios_types<char_type>::stringstream_type ss;
        ((ss << args), ...);

        auto message = ss.str();

        size_t start_pos = 0;
        size_t pos       = 0;

        std::cout << "[   COUT   ] ";
        for (auto& element : message)
        {
            if (element == 10 || element == 13)
            {
                if (start_pos != pos)
                {
                    auto print_message = message.substr(start_pos, pos - start_pos);
                    std_cout << print_message;
                }

                if (element == 10)
                {
                    std_cout << std::endl;
                    std_cout << "[   COUT   ] ";
                }

                start_pos = pos + 1;
            }
            pos++;
        }

        if (start_pos != pos)
        {
            auto print_message = message.substr(start_pos, pos - start_pos);
            std_cout << print_message;
        }

        std_cout << std::endl;
    }

    /// @brief Provide char (8-bit) strings printing.
    /// @tparam ...args_type Parameter pack type of variadic data.
    /// @param ...args Variadic data.
    template<typename... args_type>
    static void print_line(const args_type&... args)
    {
        basic_print_line<char>(args...);
    }

    /// @brief Provide wChar (16-bit) strings printing
    /// @tparam ...args_type Parameter pack type of variadic data.
    /// @param ...args Variadic data.
    template<typename... args_type>
    static void wprint_line(const args_type&... args)
    {
        basic_print_line<wchar_t>(args...);
    }
};

} // namespace callisto::framework