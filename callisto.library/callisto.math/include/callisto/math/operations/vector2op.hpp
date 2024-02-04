#pragma once

// std
#include <cmath>
// project
#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/math/primitives/line2.hpp>

namespace callisto::math
{

struct vector2op
{
    template<typename type>
    inline static constexpr auto square_of_length(const vector2<type>& vector) noexcept
    {
        auto& x = vector.x;
        auto& y = vector.y;

        return x * x + y * y;
    }

    template<typename type>
    inline static constexpr auto length(const vector2<type>& vector) noexcept
    {
        double square_len = square_of_length(vector);
        return std::sqrt(square_len);
    }

    template<typename type>
    inline static constexpr auto
    normalize(const vector2<type>& vector, double normalize_value = 1.0) noexcept
    {
        auto scale = normalize_value / length(vector);

        auto x = vector.x * scale;
        auto y = vector.y * scale;

        return vector2<decltype(x)>(x, y);
    }

    template<typename type_1, typename type_2>
    inline static constexpr auto
    dot_product(const vector2<type_1>& vec1, const vector2<type_2>& vec2) noexcept
    {
        auto& x1 = vec1.x;
        auto& y1 = vec1.y;

        auto& x2 = vec2.x;
        auto& y2 = vec2.y;

        return x1 * x2 + y1 * y2;
    }

    template<typename type_1, typename type_2>
    inline static constexpr auto
    cos_angle(const vector2<type_1>& vec1, const vector2<type_2>& vec2, double eps = 1e-9) noexcept
    {
        auto dot_prod       = dot_product(vec1, vec2);
        auto prod_of_length = length(vec1) * length(vec2);

        return dot_prod / (prod_of_length + eps);
    }

    template<typename type_1, typename type_2>
    inline static constexpr auto angle(const vector2<type_1>& vec1, const vector2<type_2>& vec2, double eps = 1e-9) noexcept
    {
        auto cos_value = cos_angle(vec1, vec2, eps);

        return std::acos(cos_value);
    }

    template<typename type_1, typename type_2>
    inline static constexpr auto
    pseudo_scalar_product(const vector2<type_1>& vec1, const vector2<type_2>& vec2) noexcept
    {
        auto& x1 = vec1.x;
        auto& y1 = vec1.y;

        auto& x2 = vec2.x;
        auto& y2 = vec2.y;

        return x1 * y2 - x2 * y1;
    }

    template<typename type_1, typename type_2>
    inline static constexpr auto
    sign_angle(const vector2<type_1>& vec1, const vector2<type_2>& vec2, double eps = 1e-9) noexcept
    {
        auto sign = pseudo_scalar_product(vec1, vec2) > 0.0 ? 1 : -1;

        auto angle_value = angle(vec1, vec2, eps);

        return sign * angle_value;
    }

    template<typename type>
    inline static constexpr auto from_line(const line2<type>& line) noexcept
    {
        return point2<type>(line.x2 - line.x1, line.y2 - line.y1);
    }

    template<typename type>
    static double sin(const vector2<type>& point) noexcept
    {
        auto length = vector2op::length(point);

        return point.y / length;
    }

    template<typename type>
    static double cos(const vector2<type>& point) noexcept
    {
        auto length = vector2op::length(point);

        return point.x / length;
    }
};

} // namespace callisto::math