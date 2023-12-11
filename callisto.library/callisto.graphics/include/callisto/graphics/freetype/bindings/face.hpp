#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// project
#include <callisto/opencv.hpp>
#include <callisto/framework/types/assert_traits.hpp>

#include "glyph.hpp"

namespace callisto::graphics::freetype
{

namespace
{
namespace c_cv = callisto::opencv;
}

class face
{
    // data
    FT_Face __handler = nullptr;

    // private methods
    void __destroy() noexcept;

    void __move_from(face&& face);

public:
    // construct and destruct
    face(FT_Face handler);

    face(const face&) = delete;

    face(face&& face);

    ~face();

    // methods
    void set_pixel_sizes(FT_UInt pixel_width, FT_UInt pixel_height);

    void load_char(FT_ULong char_code, FT_Int32 load_flags);

    void load_glyph(FT_UInt glyph_index, FT_Int32 load_flags);

    void render_glyph(FT_Render_Mode render_mode);

    FT_UInt get_char_index(FT_ULong char_code);

    cv::Mat get_bitmap_mat_present();

    glyph get_glyph();

    // getters and setters
    FT_Face get_handler();

    const FT_Face get_handler() const;

    // operators
    face& operator=(const face&) = delete;

    face& operator=(face&& face);
};

CALLISTO_ASSERT_TRAIT_ONLY_MOVE(face);

} // namespace callisto::graphics::freetype
