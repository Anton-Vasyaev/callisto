// parent header
#include <callisto/framework/types/ios_types.hpp>

namespace callisto::framework
{

std::ostream& ios_types<char>::std_cout() { return std::cout; }

std::ostream& ios_types<char>::std_cerr() { return std::cerr; }

std::istream& ios_types<char>::std_cin() { return std::cin; }


std::wostream& ios_types<wchar_t>::std_cout() { return std::wcout; }

std::wostream& ios_types<wchar_t>::std_cerr() { return std::wcerr; }

std::wistream& ios_types<wchar_t>::std_cin() { return std::wcin; }

}