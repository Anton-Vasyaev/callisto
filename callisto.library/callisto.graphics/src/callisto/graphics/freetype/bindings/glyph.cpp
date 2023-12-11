// parent header
#include <callisto/graphics/freetype/bindings/glyph.hpp>
// project
#include <callisto/graphics/freetype/exception.hpp>

namespace callisto::graphics::freetype
{
#pragma region private_methods

void glyph::__move_from(glyph&& glyph)
{
    __handler       = glyph.__handler;
    glyph.__handler = nullptr;
}

void glyph::__destroy()
{
    if (__handler != nullptr)
    {
        FT_Done_Glyph(__handler);
    }
    __handler = nullptr;
}

#pragma endregion

#pragma region construct and destruct

glyph::glyph(FT_Glyph handler) { __handler = handler; }

glyph::glyph(glyph&& glyph) { __move_from(std::move(glyph)); }

glyph::~glyph() { __destroy(); }

#pragma endregion

#pragma region methods

glyph glyph::copy() const
{
    FT_Glyph handler;

    WRAP_CALL_FREETYPE_FUNC(FT_Glyph_Copy, __handler, &handler);

    return glyph(handler);
}

bitmap_glyph glyph::to_bitmap(FT_Render_Mode render_mode, FT_Vector* origin)
{
    auto bitmap_handler = __handler;
    FT_Glyph_To_Bitmap(&bitmap_handler, render_mode, origin, false);

    return bitmap_glyph(bitmap_handler);
}

void glyph::stroke_border(stroker& stroker, FT_Bool inside)
{
    WRAP_CALL_FREETYPE_FUNC(FT_Glyph_StrokeBorder, &__handler, stroker.get_handler(), inside, true);
}

#pragma endregion

#pragma region getters_and_setters

FT_Glyph glyph::get_handler() { return __handler; }

const FT_Glyph glyph::get_handler() const { return __handler; }

#pragma endregion

#pragma region operators

glyph& glyph::operator=(glyph&& glyph)
{
    __destroy();
    __move_from(std::move(glyph));

    return *this;
}

#pragma endregion

} // namespace callisto::graphics::freetype