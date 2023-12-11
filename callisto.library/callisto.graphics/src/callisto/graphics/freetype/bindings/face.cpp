// parent header
#include "callisto/graphics/freetype/bindings/face.hpp"
// std
#include <sstream>
// 3rd party
#include <nameof.hpp>
// project
#include <callisto/opencv/auxiliary.hpp>
#include <callisto/framework/exception.hpp>

#include <callisto/graphics/freetype/bindings/bitmap_auxiliary.hpp>
#include <callisto/graphics/freetype/exception.hpp>
#include <callisto/graphics/freetype/enum/pixel_mode.hpp>

namespace callisto::graphics::freetype
{

#pragma region private_methods

void face::__destroy() noexcept
{
    if (__handler != nullptr)
    {
        FT_Done_Face(__handler);
    }
    __handler = nullptr;
}

void face::__move_from(face&& face)
{
    __handler      = face.__handler;
    face.__handler = nullptr;
}

#pragma endregion

#pragma region construct_and_destruct

face::face(FT_Face handler) { __handler = handler; }

face::face(face&& face) { __move_from(std::move(face)); }

face::~face() { __destroy(); }

#pragma endregion

#pragma region methods

void face::set_pixel_sizes(FT_UInt pixel_width, FT_UInt pixel_height)
{
    WRAP_CALL_FREETYPE_FUNC(FT_Set_Pixel_Sizes, __handler, pixel_width, pixel_height);
}

void face::load_char(FT_ULong char_code, FT_Int32 load_flags)
{
    WRAP_CALL_FREETYPE_FUNC(FT_Load_Char, __handler, char_code, load_flags);
}

void face::load_glyph(FT_UInt glyph_index, FT_Int32 load_flags)
{
    WRAP_CALL_FREETYPE_FUNC(FT_Load_Glyph, __handler, glyph_index, load_flags);
}

void face::render_glyph(FT_Render_Mode render_mode)
{
    WRAP_CALL_FREETYPE_FUNC(FT_Render_Glyph, __handler->glyph, render_mode);
}

FT_UInt face::get_char_index(FT_ULong char_code) { return FT_Get_Char_Index(__handler, char_code); }

cv::Mat face::get_bitmap_mat_present()
{
    return bitmap_auxiliary::get_mat_present(__handler->glyph->bitmap);
}

glyph face::get_glyph()
{
    FT_Glyph glyph__handler;
    WRAP_CALL_FREETYPE_FUNC(FT_Get_Glyph, __handler->glyph, &glyph__handler);

    return glyph(glyph__handler);
}

#pragma endregion

#pragma region getters_and_setters

FT_Face face::get_handler() { return __handler; }

const FT_Face face::get_handler() const { return __handler; }

#pragma endregion

#pragma region operators

face& face::operator=(face&& face)
{
    __destroy();
    __move_from(std::move(face));
    return *this;
}

#pragma endregion
} // namespace callisto::graphics::freetype