#pragma once

// project
#include "bitmap_glyph.hpp"
#include "stroker.hpp"

namespace callisto::graphics::freetype
{

namespace
{
namespace c_cv = callisto::opencv;
}

class glyph
{
    FT_Glyph _handler = nullptr;

public:
    // deleted functions
    glyph(const glyph&) = delete;

    const glyph& operator=(const glyph&) = delete;

    const glyph& operator=(glyph&&) = delete;

    // construct and destruct
    glyph(FT_Glyph handler);

    glyph(glyph&& glyph);

    ~glyph();

    // methods
    glyph copy() const;

    bitmap_glyph to_bitmap(FT_Render_Mode render_mode, FT_Vector* origin = nullptr);

    void stroke_border(stroker& stroker, FT_Bool inside);

    // getters and setters
    FT_Glyph get_handler();

    const FT_Glyph get_handler() const;
};

} // namespace callisto::graphics::freetype