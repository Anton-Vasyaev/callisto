#pragma once

// std
#include <string>

namespace callisto::framework
{
std::wstring str2wide(const std::string& str)
{
    return std::wstring(std::begin(str), std::end(str));
}

std::string cut_wide2str(const std::wstring& str)
{
    return std::string(std::begin(str), std::end(str));
}
} // namespace callisto::framework