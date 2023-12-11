// parent header
#include <callisto/graphics/freetype/bindings/bitmap_glyph.hpp>
// project
#include <callisto/graphics/freetype/exception.hpp>
#include <callisto/graphics/freetype/bindings/bitmap_auxiliary.hpp>

namespace callisto::graphics::freetype
{

#pragma region private_methods

void bitmap_glyph::__destroy() noexcept
{
    if (__handler != nullptr)
    {
        FT_Done_Glyph(__handler);
    }
    __handler = nullptr;
}

void bitmap_glyph::__move_from(bitmap_glyph&& glyph)
{
    __handler       = glyph.__handler;
    glyph.__handler = nullptr;
}

#pragma endregion

#pragma region construct_and_destruct

bitmap_glyph::bitmap_glyph(FT_Glyph handler) { __handler = handler; }

bitmap_glyph::bitmap_glyph(bitmap_glyph&& glyph) { __move_from(std::move(glyph)); }

bitmap_glyph::~bitmap_glyph() { __destroy(); }

#pragma endregion

#pragma region methods

cv::Mat bitmap_glyph::get_mat_present()
{
    auto bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(__handler);

    return bitmap_auxiliary::get_mat_present(bitmap_glyph->bitmap);
}

#pragma endregion

#pragma region getters_and_setters

FT_BitmapGlyph bitmap_glyph::get_handler() { return reinterpret_cast<FT_BitmapGlyph>(__handler); }

const FT_BitmapGlyph bitmap_glyph::get_handler() const
{
    return reinterpret_cast<const FT_BitmapGlyph>(__handler);
}

#pragma endregion

#pragma region operators

bitmap_glyph& bitmap_glyph::operator=(bitmap_glyph&& glyph)
{
    __destroy();
    __move_from(std::move(glyph));

    return *this;
}

#pragma endregion

} // namespace callisto::graphics::freetype
