// parent header
#include <callisto/graphics/typing/data/typing_garniture.hpp>

namespace callisto::graphics
{
#pragma region private_method

void typing_garniture::move_from(typing_garniture&& garniture)
{
    _symbols_data = std::move(garniture._symbols_data);

    _render_height_size = garniture._render_height_size;
    _space_hori_advance = garniture._space_hori_advance;
    _space_vert_advance = garniture._space_vert_advance;
}

#pragma endregion

#pragma region construct_and_destruct

typing_garniture::typing_garniture(
    int32_t render_height_size,
    int32_t space_hori_advance,
    int32_t space_vert_advance
)
{
    _render_height_size = render_height_size;
    _space_hori_advance = space_hori_advance;
    _space_vert_advance = space_vert_advance;
}

typing_garniture::typing_garniture(typing_garniture&& garniture)
{
    move_from(std::move(garniture));
}

#pragma endregion

#pragma region methods

typing_garniture typing_garniture::clone() const
{
    auto new_garniture
        = typing_garniture(_render_height_size, _space_hori_advance, _space_vert_advance);

    for (auto& item : _symbols_data) { new_garniture.add_symbol(item.first, item.second.clone()); }

    return std::move(new_garniture);
}

void typing_garniture::add_symbol(int64_t symbol_code, font_symbol_data& symbol_data)
{
    _symbols_data.emplace(symbol_code, symbol_data.clone());
}

void typing_garniture::add_symbol(int64_t symbol_code, font_symbol_data&& symbol_data)
{
    _symbols_data.emplace(symbol_code, std::move(symbol_data));
}

font_symbol_data& typing_garniture::get_symbol_data(int64_t symbol_code)
{
    return _symbols_data.at(symbol_code);
}

const font_symbol_data& typing_garniture::get_symbol_data(int64_t symbol_code) const
{
    return _symbols_data.at(symbol_code);
}

#pragma endregion

#pragma region getters_and_setters

int32_t typing_garniture::get_render_height_size() const { return _render_height_size; }

int32_t typing_garniture::get_space_hori_advance() const { return _space_hori_advance; }

int32_t typing_garniture::get_space_vert_advance() const { return _space_vert_advance; }

typing_garniture::symbols_data_type& typing_garniture::get_symbols_data() { return _symbols_data; }

const typing_garniture::symbols_data_type& typing_garniture::get_symbols_data() const
{
    return _symbols_data;
}

#pragma endregion

#pragma region operators

const typing_garniture& typing_garniture::operator=(typing_garniture&& garniture)
{
    move_from(std::move(garniture));

    return *this;
}

#pragma endregion
} // namespace callisto::graphics