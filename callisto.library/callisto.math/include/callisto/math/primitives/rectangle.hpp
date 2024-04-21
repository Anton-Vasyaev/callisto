#pragma once

// project
#include <callisto/framework/concepts.hpp>
#include "alg_tuple2.hpp"

namespace callisto::math
{

template<callisto::framework::concept_arithmetic _value_type>
struct rectangle
{
    using value_type = _value_type;

    using position_type = point2<value_type>;

    using size_type = size2<value_type>;

    value_type x;

    value_type y;

    value_type width;

    value_type height;

#pragma region static_methods

    inline static constexpr rectangle empty() noexcept { return rectangle(0, 0, 0, 0); }

#pragma endregion

#pragma region construct_and_destruct

    inline constexpr rectangle() noexcept {}

    inline constexpr rectangle(
        value_type x,
        value_type y,
        value_type width,
        value_type height
    ) noexcept
    {
        this->x = x;
        this->y = y;

        this->width  = width;
        this->height = height;
    }

    inline constexpr rectangle(
        const point2<value_type>& position,
        const size2<value_type>&  size
    ) noexcept
    {
        x = position.x;
        y = position.y;

        width  = size.width;
        height = size.height;
    }

#pragma endregion

#pragma region methods

    template<callisto::framework::concept_arithmetic cast_type>
    inline constexpr auto as() const noexcept
    {
        return rectangle<cast_type>(x, y, width, height);
    }

    inline constexpr point2<value_type> center() const noexcept
    {
        auto x_c = x + width / 2;
        auto y_c = y + height / 2;

        return point2<value_type>(x_c, y_c);
    }

    inline constexpr point2<value_type> position() const noexcept
    {
        return point2<value_type>(x, y);
    }

    inline void set_position(const point2<value_type>& point) noexcept
    {
        x = point.x;
        y = point.y;
    }

    inline constexpr size2<value_type> size() const noexcept
    {
        return size2<value_type>(width, height);
    }

    inline void set_size(const size2<value_type> size) noexcept
    {
        width  = size.width;
        height = size.height;
    }

#pragma endregion

#pragma region operators

    inline constexpr bool operator==(const rectangle& other) const noexcept
    {
        return x == other.x && y == other.y && other.width == width && other.height == height;
    }

    inline constexpr bool operator!=(const rectangle& other) const noexcept
    {
        return x != other.x || y != other.y || width != width || height != height;
    }

#pragma endregion
};

template<callisto::framework::concept_arithmetic type>
rectangle(type, type, type, type) -> rectangle<type>;

template<typename alg_tuple2_type>
rectangle(alg_tuple2_type, alg_tuple2_type) -> rectangle<alg_tuple2_type>;

using rectangle_i = rectangle<int32_t>;

using rectangle_l = rectangle<int64_t>;

using rectangle_f = rectangle<float>;

using rectangle_d = rectangle<double>;

} // namespace callisto::math