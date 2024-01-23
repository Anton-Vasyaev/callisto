#pragma once

// std
#include <cstdint>
#include <utility>
// 3rd party
#include <callisto/framework/concepts.hpp>
#include <callisto/framework/types/type_traits.hpp>

namespace callisto::math
{

// imports
namespace
{
namespace c_f = callisto::framework;
}

template<c_f::concept_fundamental _value_type>
struct alg_tuple2
{
    using value_type = _value_type;

    union
    {
        value_type v1;
        value_type x;
        value_type width;
    };

    union
    {
        value_type v2;
        value_type y;
        value_type height;
    };

    inline static constexpr alg_tuple2 empty() noexcept { return alg_tuple2(0, 0); }

#pragma region construct_and_destruct

    inline constexpr alg_tuple2() noexcept {}

    template<typename type_1, typename type_2>
    inline constexpr alg_tuple2(type_1 v1, type_2 v2) noexcept
    {
        this->v1 = v1;
        this->v2 = v2;
    }

    template<typename other_type>
    inline constexpr alg_tuple2(const alg_tuple2<other_type>& values) noexcept
    {
        v1 = values.v1;
        v2 = values.v2;
    }

#pragma endregion

#pragma region methods

    template<typename cast_type>
    inline constexpr auto as() const noexcept
    {
        return alg_tuple2<cast_type>(v1, v2);
    }

#pragma endregion

#pragma region operators

    template<typename other_type>
    inline constexpr const alg_tuple2& operator=(const alg_tuple2<other_type>& other_tuple) noexcept
    {
        v1 = other_tuple.v1;
        v2 = other_tuple.v2;

        return *this;
    }

    // ADDITION
    template<typename other_type>
    inline constexpr auto operator+(const alg_tuple2<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v2);

        return alg_tuple2<num_type>(v1 + other_tuple.v1, v2 + other_tuple.v2);
    }

    template<typename numeric_type>
    inline constexpr auto operator+(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple2<num_type>(v1 + value, v2 + value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple2& operator+=(const alg_tuple2<other_type>& other_tuple
    ) noexcept
    {
        v1 += other_tuple.v1;
        v2 += other_tuple.v2;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple2& operator+=(numeric_type value) noexcept
    {
        v1 += value;
        v2 += value;

        return *this;
    }

    // SUBSTRACTION
    template<typename other_type>
    inline constexpr auto operator-(const alg_tuple2<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v2);

        return alg_tuple2<num_type>(v1 - other_tuple.v1, v2 - other_tuple.v2);
    }

    template<typename numeric_type>
    inline constexpr auto operator-(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple2<num_type>(v1 - value, v2 - value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple2& operator-=(const alg_tuple2<other_type>& other_tuple
    ) noexcept
    {
        v1 -= other_tuple.v1;
        v2 -= other_tuple.v2;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple2& operator-=(numeric_type value) noexcept
    {
        v1 -= value;
        v2 -= value;

        return *this;
    }

    // MULTIPLICATION
    template<typename other_type>
    inline constexpr auto operator*(const alg_tuple2<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v2);

        return alg_tuple2<num_type>(v1 * other_tuple.v1, v2 * other_tuple.v2);
    }

    template<typename numeric_type>
    inline constexpr auto operator*(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple2<num_type>(v1 * value, v2 * value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple2& operator*=(const alg_tuple2<other_type>& other_tuple
    ) noexcept
    {
        v1 *= other_tuple.v1;
        v2 *= other_tuple.v2;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple2& operator*=(numeric_type value) noexcept
    {
        v1 *= value;
        v2 *= value;

        return *this;
    }

    // DIVISION
    template<typename other_type>
    inline constexpr auto operator/(const alg_tuple2<other_type>& other_tuple) const noexcept
    {
        using num_type = decltype(v1 + other_tuple.v2);

        return alg_tuple2<num_type>(v1 / other_tuple.v1, v2 / other_tuple.v2);
    }

    template<typename numeric_type>
    inline constexpr auto operator/(numeric_type value) const noexcept
    {
        using num_type = decltype(v1 + value);

        return alg_tuple2<num_type>(v1 / value, v2 / value);
    }

    template<typename other_type>
    inline constexpr const alg_tuple2& operator/=(const alg_tuple2<other_type>& other_tuple
    ) noexcept
    {
        v1 /= other_tuple.v1;
        v2 /= other_tuple.v2;

        return *this;
    }

    template<typename numeric_type>
    inline constexpr const alg_tuple2& operator/=(numeric_type value) noexcept
    {
        v1 /= value;
        v2 /= value;

        return *this;
    }

    template<typename other_type>
    inline constexpr bool operator==(const alg_tuple2<other_type>& other_tuple) noexcept
    {
        return v1 == other_tuple.v1 && v2 == other_tuple.v2;
    }

    template<typename other_type>
    inline constexpr bool operator!=(const alg_tuple2<other_type>& other_tuple) noexcept
    {
        return v1 != other_tuple.v1 || v2 != other_tuple.v2;
    }

#pragma endregion
};

template<typename type_1, typename type_2>
alg_tuple2(type_1, type_2) -> alg_tuple2<c_f::senior_conversion_t<type_1, type_2>>;

#pragma region alias

using alg_tuple2i = alg_tuple2<int32_t>;

using alg_tuple2l = alg_tuple2<int64_t>;

using alg_tuple2f = alg_tuple2<float>;

using alg_tuple2d = alg_tuple2<double>;

template<typename type>
using point2 = alg_tuple2<type>;

using point2i = point2<int32_t>;

using point2l = point2<int64_t>;

using point2f = point2<float>;

using point2d = point2<double>;

template<typename type>
using vector2 = alg_tuple2<type>;

using vector2i = vector2<int32_t>;

using vector2l = vector2<int64_t>;

using vector2f = vector2<float>;

using vector2d = vector2<double>;

template<typename type>
using size2 = alg_tuple2<type>;

using size2i = size2<int32_t>;

using size2l = size2<int64_t>;

using size2f = size2<float>;

using size2d = size2<double>;

#pragma endregion

} // namespace callisto::math