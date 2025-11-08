// parent header
#include <callisto/opencv/data/window_press_key.hpp>

namespace callisto::opencv
{

window_press_key window_press_key_from_code(int code)
{
    if (code >= 65 && code <= 90)
    {
        code -= 64;
        return static_cast<window_press_key>(code);
    }

    if (code >= 97 && code <= 122)
    {
        return static_cast<window_press_key>(code - 96);
    }

    switch (code)
    {
        case 27 : return window_press_key::escape;
        case 32 : return window_press_key::space;
        case 96 : return window_press_key::tilda;
        case 9 : return window_press_key::tab;
        case 13 : return window_press_key::enter;
        case 8 : return window_press_key::backspace;
        case 92 : return window_press_key::slashes;
        default : return window_press_key::UNKNOWN;
    }
}

} // namespace callisto::opencv