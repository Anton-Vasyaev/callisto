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

inline static font_symbol_metrics create_metrics_from_freetype(FT_Glyph_Metrics metrics)
{
    float hori_bearing_x = metrics.horiBearingX / 64.0;
    float hori_bearing_y = metrics.horiBearingY / 64.0;
    float hori_advance   = metrics.horiAdvance / 64.0;

    float vert_bearing_x = metrics.vertBearingX / 64.0;
    float vert_bearing_y = metrics.vertBearingY / 64.0;
    float vert_advance   = metrics.vertAdvance / 64.0;

    return { hori_bearing_x, hori_bearing_y, hori_advance, vert_bearing_x,
             vert_bearing_y, vert_advance,   true };
}

template<typename sequence_type>
typing_garniture build_garniture_freetype(
    freetype::face&      face,
    const sequence_type& char_indexes,
    int32_t              render_pixel_size,
    FT_Int32             load_target

)
{
    face.set_pixel_sizes(0, render_pixel_size);

    auto space_glyph_idx = face.get_char_index(32);
    face.load_glyph(space_glyph_idx, FT_LOAD_NO_BITMAP);
    auto space_metrics      = face.get_handler()->glyph->metrics;
    auto space_hori_advance = space_metrics.horiAdvance / 64;
    auto space_vert_advance = space_metrics.vertAdvance / 64;

    auto garniture = typing_garniture(render_pixel_size, space_hori_advance, space_vert_advance);

    for (const auto& char_idx : char_indexes)
    {
        auto glyph_idx = face.get_char_index(char_idx);
        face.load_glyph(glyph_idx, load_target | FT_LOAD_RENDER);

        auto font_mat = face.get_bitmap_mat_present().clone();

        auto metrics = create_metrics_from_freetype(face.get_handler()->glyph->metrics);

        auto data = font_symbol_data(metrics, std::move(font_mat));

        garniture.add_symbol(char_idx, std::move(data));
    }

    return garniture;
}
} // namespace callisto::graphics