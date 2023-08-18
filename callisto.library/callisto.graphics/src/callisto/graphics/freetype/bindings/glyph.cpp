// parent header
#include <callisto/graphics/freetype/bindings/glyph.hpp>
// project
#include <callisto/graphics/freetype/exception.hpp>

namespace callisto::graphics::freetype
{
#pragma region construct and destruct

glyph::glyph(FT_Glyph handler) { _handler = handler; }

glyph::glyph(glyph&& glyph)
{
    _handler       = glyph._handler;
    glyph._handler = nullptr;
}

glyph::~glyph()
{
    if (_handler != nullptr) { FT_Done_Glyph(_handler); }
}

#pragma endregion

#pragma region methods

glyph glyph::copy() const
{
    FT_Glyph handler;

    WRAP_CALL_FREETYPE_FUNC(FT_Glyph_Copy, _handler, &handler);

    return glyph(handler);
}

bitmap_glyph glyph::to_bitmap(FT_Render_Mode render_mode, FT_Vector* origin)
{
    auto bitmap_handler = _handler;
    FT_Glyph_To_Bitmap(&bitmap_handler, render_mode, origin, false);

    return bitmap_glyph(bitmap_handler);
}

void glyph::stroke_border(stroker& stroker, FT_Bool inside)
{
    WRAP_CALL_FREETYPE_FUNC(FT_Glyph_StrokeBorder, &_handler, stroker.get_handler(), inside, true);
}

#pragma endregion

// getters and setters
FT_Glyph glyph::get_handler() { return _handler; }

const FT_Glyph glyph::get_handler() const { return _handler; }
} // namespace callisto::graphics::freetype