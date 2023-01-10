#pragma once

// std
#include <unordered_map>
// project
#include "font_symbol_data.hpp"

namespace callisto::graphics
{

namespace
{
namespace c_cv = callisto::opencv;
}

class typing_garniture
{
    // data
    std::unordered_map<int64_t, font_symbol_data> _symbols_data;

    c_cv::image_type _image_type;

    int32_t _render_height_size;

    int32_t _space_hori_advance;

    int32_t _space_vert_advance;

    // private method
    void move_from(typing_garniture&& garniture);

public:
    // deleted functions
    typing_garniture(const typing_garniture&) = delete;

    const typing_garniture& operator=(typing_garniture&) = delete;

    // construct and destruct
    typing_garniture(
        int32_t render_height_size,
        int32_t space_hori_advance,
        int32_t space_vert_advance
    );

    typing_garniture(typing_garniture&& garniture);

    // methods
    typing_garniture clone() const;

    void add_symbol(int64_t symbol_code, font_symbol_data& symbol_data);

    void add_symbol(int64_t symbol_code, font_symbol_data&& symbol_data);

    font_symbol_data& get_symbol_data(int64_t symbol_code);

    const font_symbol_data& get_symbol_data(int64_t symbol_code) const;

    // getters and setters
    int32_t get_render_height_size() const;

    int32_t get_space_hori_advance() const;

    int32_t get_space_vert_advance() const;

    // operators
    const typing_garniture& operator=(typing_garniture&& garniture);
};

} // namespace callisto::graphics