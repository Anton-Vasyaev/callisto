#pragma once

// project
#include <callisto/framework/types/assert_traits.hpp>

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
    // data
    FT_Glyph __handler = nullptr;

    // private methods
    void __move_from(glyph&& glyph);

    void __destroy();

public:
    // construct and destruct
    glyph(FT_Glyph handler);

    glyph(const glyph&) = delete;

    glyph(glyph&& glyph);

    ~glyph();

    // methods
    glyph copy() const;

    bitmap_glyph to_bitmap(FT_Render_Mode render_mode, FT_Vector* origin = nullptr);

    void stroke_border(stroker& stroker, FT_Bool inside);

    // getters and setters
    FT_Glyph get_handler();

    const FT_Glyph get_handler() const;

    // operators
    glyph& operator=(const glyph&) = delete;

    glyph& operator=(glyph&&);
};

CALLISTO_ASSERT_TRAIT_ONLY_MOVE(glyph);

} // namespace callisto::graphics::freetype