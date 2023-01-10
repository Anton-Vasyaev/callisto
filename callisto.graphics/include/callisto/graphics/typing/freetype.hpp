#pragma once

// project
#include <callisto/framework/string.hpp>

#include "data/typing_garniture.hpp"
#include <callisto/graphics/freetype.hpp>

namespace callisto::graphics
{

namespace
{
namespace c_f = callisto::framework;
}

void validate_render_mode(FT_Render_Mode render_mode)
{
    if (render_mode != FT_RENDER_MODE && FT_RENDER_MODE_LCD) }

template<typename sequence_type>
typing_garniture build_garniture_freetype(
    freetype::face&      face,
    const sequence_type& char_indexes,
    int32_t              render_pixel_size,
    FT_Render_Mode       render_mode

)
{
    face.set_pixel_sizes(0, render_pixel_size);

    auto space_glyph_idx = face.get_char_index(32);
    face.load_glyph(glyph_idx, FT_LOAD_NO_BITMAP);
    auto space_metrics      = face.get_handler()->glyph->metrics;
    auto space_hori_advance = space_metrics.horiAdvance / 64;
    auto space_vert_advance = space_metrics.vertAdvance / 64;

    auto garniture = typing_garniture(render_pixel_size, space_hori_advance, space_vert_advance);

    for (const auto& char_idx : char_indexes) {}
}
} // namespace callisto::graphics