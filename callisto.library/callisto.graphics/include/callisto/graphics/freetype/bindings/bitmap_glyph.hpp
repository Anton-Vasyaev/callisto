#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
// project
#include <callisto/framework/types/assert_traits.hpp>
#include <callisto/opencv.hpp>

namespace callisto::graphics::freetype
{

class bitmap_glyph
{
    // data
    FT_Glyph __handler = nullptr;

    // private methods
    void __destroy() noexcept;

    void __move_from(bitmap_glyph&& glyph);

public:
    // construct and destruct
    bitmap_glyph(FT_Glyph handler);

    // construct and destruct
    bitmap_glyph(const bitmap_glyph&) = delete;

    bitmap_glyph(bitmap_glyph&& glyph);

    ~bitmap_glyph();

    // methods
    cv::Mat get_mat_present();

    // getters and setters
    FT_BitmapGlyph get_handler();

    const FT_BitmapGlyph get_handler() const;

    // operators
    bitmap_glyph& operator=(const bitmap_glyph&) = delete;

    bitmap_glyph& operator=(bitmap_glyph&& glyph);
};

CALLISTO_ASSERT_TRAIT_ONLY_MOVE(bitmap_glyph);

} // namespace callisto::graphics::freetype