#pragma once

// std
#include <iostream>
#include <sstream>
#include <fstream>

namespace callisto::framework
{

/// @brief Provides types of streams for char type.
/// @tparam _char_type Char type.
template<typename _char_type>
struct ios_types;

template<>
struct ios_types<char>
{
    /// @brief Instatiation type of @see std::basic_stringstream.
    using stringstream_type = std::stringstream;

    /// @brief Instatiation type of @see std::basic_fstream.
    using fstream_type = std::fstream;

    /// @brief Instatiation type of @see std::basic_ifstream.
    using ifstream_type = std::ifstream;

    /// @brief Instatiation type of @see std::basic_ofstream.
    using ofstream_type = std::ofstream;

    /// @brief Instatiation type of @see std::basic_ostream console output.
    static std::ostream& std_cout();

    /// @brief Instatiation type of @see std::basic_ostream console error output.
    static std::ostream& std_cerr();

    /// @brief Instatiation type of @see std::basic_istream console input.
    static std::istream& std_cin();
};

template<>
struct ios_types<wchar_t>
{
    /// @brief Instatiation type of basic_stringstream
    using stringstream_type = std::wstringstream;

    /// @brief Instatiation type of @see std::basic_fstream.
    using fstream_type = std::wfstream;

    /// @brief Instatiation type of @see std::basic_ifstream.
    using ifstream_type = std::wifstream;

    /// @brief Instatiation type of @see std::basic_ofstream.
    using ofstream_type = std::wofstream;

    /// @brief Instatiation type of @see std::basic_ostream console output.
    static std::wostream& std_cout();

    /// @brief Instatiation type of @see std::basic_ostream console error output.
    static std::wostream& std_cerr();

    /// @brief Instatiation type of @see std::basic_istream console input.
    static std::wistream& std_cin();
};

} // namespace callisto::framework