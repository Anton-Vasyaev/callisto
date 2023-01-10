// parent header
#include <callisto/graphics/freetype/bindings/bitmap_glyph.hpp>
// project
#include <callisto/graphics/freetype/exception.hpp>
#include <callisto/graphics/freetype/bindings/bitmap_auxiliary.hpp>

namespace callisto::graphics::freetype
{

#pragma region construct_and_destruct

bitmap_glyph::bitmap_glyph(FT_Glyph handler) { _handler = handler; }

bitmap_glyph::bitmap_glyph(bitmap_glyph&& glyph)
{
    _handler       = glyph._handler;
    glyph._handler = nullptr;
}

bitmap_glyph::~bitmap_glyph()
{
    if (_handler != nullptr) { FT_Done_Glyph(_handler); }
}

#pragma endregion

#pragma region methods

cv::Mat bitmap_glyph::get_mat_present()
{
    auto bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(_handler);

    return bitmap_auxiliary::get_mat_present(bitmap_glyph->bitmap);
}

#pragma endregion

#pragma region getters_and_setters

FT_BitmapGlyph bitmap_glyph::get_handler() { return reinterpret_cast<FT_BitmapGlyph>(_handler); }

const FT_BitmapGlyph bitmap_glyph::get_handler() const
{
    return reinterpret_cast<const FT_BitmapGlyph>(_handler);
}

#pragma endregion

} // namespace callisto::graphics::freetype
