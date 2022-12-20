#pragma once

// std
#include <cstring>
#include <cwchar>

namespace callisto::framework
{


/// @brief Returns length of null-terminated string.
/// @tparam str_type Type of char.
/// @param str Pointer to string.
/// @return Length of string.
template<typename str_type>
inline size_t strlen(const str_type* str);

/// @brief Returns length of null-terminated 8-bit string (char).
/// @param str Pointer to string.
/// @return Length of string.
template<>
inline size_t strlen<char>(const char* str)
{
    return std::strlen(str);
}

/// @brief Returns length of null-terminated 16-bit string (wchar_t).
/// @param str Pointer to string.
/// @return Length of string.
template<>
inline size_t strlen<wchar_t>(const wchar_t* str)
{
    return std::wcslen(str);
}

}; // namespace callisto::framework