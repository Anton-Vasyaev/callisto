#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

namespace callisto::graphics::freetype
{

constexpr const char* pixel_mode_str(FT_Pixel_Mode mode)
{
    switch (mode)
    {
        case FT_PIXEL_MODE_MONO : return "Mono";
        case FT_PIXEL_MODE_GRAY : return "Gray";
        case FT_PIXEL_MODE_GRAY2 : return "Gray2";
        case FT_PIXEL_MODE_GRAY4 : return "Gray4";
        case FT_PIXEL_MODE_LCD : return "LCD";
        case FT_PIXEL_MODE_LCD_V : return "LCD_V";
        case FT_PIXEL_MODE_BGRA : return "BGRA";
        case FT_PIXEL_MODE_MAX : return "Max";

        default : return "None";
    }
}

inline constexpr const char* pixel_mode_str(unsigned char mode)
{
    return pixel_mode_str((FT_Pixel_Mode)mode);
}

} // namespace callisto::graphics::freetype