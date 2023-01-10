#pragma once

// 3rd party
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
// project
#include <callisto/opencv.hpp>

#include "glyph.hpp"

namespace callisto::graphics::freetype
{

namespace
{
namespace c_cv = callisto::opencv;
}

class face
{
private:
    FT_Face _handler = nullptr;

public:
    // deleted functions
    face(const face&) = delete;

    const face& operator=(const face&) = delete;

    const face& operator=(face&&) = delete;

    // construct and destruct
    face(FT_Face handler);

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
};

} // namespace callisto::graphics::freetype
