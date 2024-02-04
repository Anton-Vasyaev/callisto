#pragma once

// project
#include <callisto/framework/concepts.hpp>
#include "alg_tuple2.hpp"

namespace callisto::math
{

namespace
{
namespace c_f = callisto::framework;
}

template<c_f::concept_fundamental _type>
struct rectangle
{
    using type = _type;

    using position_type = point2<type>;

    using size_type = size2<type>;

    position_type position;

    size_type size;

#pragma region static_methods

    inline static constexpr rectangle empty() noexcept { return rectangle(0, 0, 0, 0); }

#pragma endregion

#pragma region construct_and_destruct

    inline constexpr rectangle() noexcept {}

    template<
        c_f::concept_fundamental x_type,
        c_f::concept_fundamental y_type,
        c_f::concept_fundamental w_type,
        c_f::concept_fundamental h_type>
    inline constexpr rectangle(x_type x, y_type y, w_type width, h_type height) noexcept
    {
        this->position.x = x;
        this->position.y = y;

        this->size.width  = width;
        this->size.height = height;
    }

    template<c_f::concept_fundamental pos_type, c_f::concept_fundamental size_type>
    inline constexpr rectangle(
        const point2<pos_type>& position,
        const size2<size_type>& size
    ) noexcept
    {
        this->position = position;
        this->size     = size;
    }

#pragma endregion

#pragma region operators

    template<typename other_type>
    inline constexpr bool operator==(const rectangle<other_type>& other_rect) noexcept
    {
        return this->position == other_rect.position && this->size == other_rect.size;
    }

    template<typename other_type>
    inline constexpr bool operator!=(const rectangle<other_type>& other_rect) noexcept
    {
        return this->position != other_rect.position || this->size != other_rect.size;
    }

#pragma endregion
};

template<typename x_type, typename y_type, typename w_type, typename h_type>
rectangle(x_type, y_type, w_type, h_type)
    -> rectangle<c_f::senior_conversion_t<x_type, y_type, w_type, h_type>>;

template<typename position_type, typename size_type>
rectangle(position_type, size_type) -> rectangle<
    c_f::senior_conversion_t<typename position_type::value_type, typename size_type::value_type>>;

using rectangle_i = rectangle<int32_t>;

using rectangle_l = rectangle<int64_t>;

using rectangle_f = rectangle<float>;

using rectangle_d = rectangle<double>;

} // namespace callisto::math