#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
// project
#include <callisto/opencv.hpp>

namespace callisto::graphics::freetype
{

class bitmap_glyph
{
    FT_Glyph _handler = nullptr;

public:
    // deleted functions
    bitmap_glyph(const bitmap_glyph&) = delete;

    const bitmap_glyph& operator=(const bitmap_glyph&) = delete;

    const bitmap_glyph& operator=(bitmap_glyph&&) = delete;

    // construct and destruct
    bitmap_glyph(FT_Glyph handler);

    bitmap_glyph(bitmap_glyph&& glyph);

    ~bitmap_glyph();

    // methods
    cv::Mat get_mat_present();

    // getters and setters
    FT_BitmapGlyph get_handler();

    const FT_BitmapGlyph get_handler() const;
};

} // namespace callisto::graphics::freetype