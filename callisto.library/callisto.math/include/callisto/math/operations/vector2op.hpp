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
    template<typename vector_type>
    inline static constexpr auto square_of_length(const vector_type& vector) noexcept
    {
        auto& x = vector.x;
        auto& y = vector.y;

        return x * x + y * y;
    }

    template<typename _calc_type = void, typename vector_type = alg_tuple2i>
    inline static constexpr auto length(const vector_type& vector) noexcept
    {
        using calc_type = typename std::conditional<
            std::is_void<_calc_type>::value,
            typename vector_type::value_type,
            _calc_type>::type;

        calc_type square_len = square_of_length(vector);
        return std::sqrt(square_len);
    }

    template<
        typename _calc_type   = void,
        typename vector_type  = alg_tuple2i,
        typename numeric_type = typename vector_type::value_type>
    inline static constexpr auto
    normalize(const vector_type& vector, numeric_type normalize_value = 1.0) noexcept
    {
        using calc_type = typename std::conditional<
            std::is_void<_calc_type>::value,
            typename vector_type::value_type,
            _calc_type>::type;

        auto scale = normalize_value / length<calc_type>(vector);

        auto x = vector.x * scale;
        auto y = vector.y * scale;

        return vector_type { x, y };
    }

    template<typename vector_type>
    inline static constexpr auto
    dot_product(const vector_type& vec1, const vector_type& vec2) noexcept
    {
        auto& x1 = vec1.x;
        auto& y1 = vec1.y;

        auto& x2 = vec2.x;
        auto& y2 = vec2.y;

        return x1 * x2 + y1 * y2;
    }

    template<typename _calc_type = void, typename vector_type = alg_tuple2i>
    inline static constexpr auto
    cos_angle(const vector_type& vec1, const vector_type& vec2) noexcept
    {
        using calc_type = typename std::conditional<
            std::is_void<_calc_type>::value,
            typename vector_type::value_type,
            _calc_type>::type;

        auto dot_prod       = dot_product(vec1, vec2);
        auto prod_of_length = length<calc_type>(vec1) * length<calc_type>(vec2);

        return dot_prod / prod_of_length;
    }

    template<typename calc_type = void, typename vector_type = alg_tuple2i>
    inline static constexpr auto angle(const vector_type& vec1, const vector_type& vec2) noexcept
    {
        auto cos_value = cos_angle<calc_type>(vec1, vec2);

        return std::acos(cos_value);
    }

    template<typename vector_type>
    inline static constexpr auto
    pseudo_scalar_product(const vector_type& vec1, const vector_type& vec2) noexcept
    {
        auto& x1 = vec1.x;
        auto& y1 = vec1.y;

        auto& x2 = vec2.x;
        auto& y2 = vec2.y;

        return x1 * y2 - x2 * y1;
    }

    template<typename calc_type = void, typename vector_type = alg_tuple2i>
    inline static constexpr auto
    sign_angle(const vector_type& vec1, const vector_type& vec2) noexcept
    {
        auto sign = pseudo_scalar_product(vec1, vec2) > 0.0 ? 1 : -1;

        auto angle_value = angle<calc_type>(vec1, vec2);

        return sign * angle_value;
    }

    template<typename line2_type>
    inline static constexpr auto from_line(const line2_type& line) noexcept
    {
        return point2<typename line2_type::value_type>(line.x2 - line.x1, line.y2 - line.y1);
    }

    template<typename point_type>
    static double sin(const point_type& point) noexcept
    {
        auto length = vector2op::length<double>(point);

        return point.y / length;
    }

    template<typename point_type>
    static double cos(const point_type& point) noexcept
    {
        auto length = vector2op::length<double>(point);

        return point.x / length;
    }
};

} // namespace callisto::math