#pragma once

#include <sstream>

namespace callisto::framework
{

/// @brief Builds string present for variadic data.
/// @tparam char_type    Char Type of std::basic_string.
/// @tparam ...args_type Parameter pack type of variadic data.
/// @param ...args Variadic data.
/// @return String present.
template<typename char_type, typename... args_type>
inline auto build_string(const args_type&... args)
{
    std::basic_stringstream<char_type> ss;

    ((ss << args), ...);

    return ss.str();
}

/// @brief char-type alias of build_string.
/// @tparam ...args_type Parameter pack type of variadic data.
/// @param ...args  Variadic data.
/// @return String present.
template<typename... args_type>
inline auto _bs(const args_type&... args)
{
    return build_string<char>(args...);
}

/// @brief wchar_t-type alias of build_string.
/// @tparam ...args_type Parameter pack type of variadic data.
/// @param ...args  Variadic data.
/// @return String present.
template<typename... args_type>
inline auto _wbs(const args_type&... args)
{
    return build_string<wchar_t>(args...);
}

} // namespace callisto::framework