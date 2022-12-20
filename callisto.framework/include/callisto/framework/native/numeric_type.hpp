#pragma once

// std
#include <cstddef>
#include <cstdint>
#include <string_view>
// project
#include <callisto/framework/configuration/object_enum.hpp>

using float32_t = float;
using float64_t = double;

namespace callisto::framework
{

#define CALLISTO_NUMERIC_TYPE_FUNCTIONS            \
    inline constexpr size_t size() const noexcept; \
                                                   \
    template<typename type>                        \
    inline static constexpr numeric_type instance() noexcept;

CALLISTO_DEFINE_OBJECT_ENUM(
    numeric_type,
    CALLISTO_NUMERIC_TYPE_FUNCTIONS,
    (unknown),

    (uint8),
    (int8),

    (uint16),
    (int16),

    (uint32),
    (int32),

    (uint64),
    (int64),

    (float32),
    (float64)
);

/// @enum callisto::framework::numeric_type
/// @brief Type of native basic numeric type.

/// @fn callisto::framework::numeric_type::uint8()
/// @brief 8-bit unsigned integer type.

/// @fn callisto::framework::numeric_type::int8()
/// @brief 8-bit signed integer type.

/// @fn callisto::framework::numeric_type::uint16()
/// @brief 16-bt unsigned integer type.

/// @fn callisto::framework::numeric_type::int16()
/// @brief 16-bit signed integer type.

/// @fn callisto::framework::numeric_type::uint32()
/// @brief 32-bit unsigned integer type.

/// @fn callisto::framework::numeric_type::int32()
/// @brief 32-bit signed integer type.

/// @fn callisto::framework::numeric_type::uint64()
/// @brief 64-bit unsigned integer type.

/// @fn callisto::framework::numeric_type::int64()
/// @brief 64-bit signed integer type.

/// @fn callisto::framework::numeric_type::float32()
/// @brief 32-bit floating point type.

/// @fn callisto::framework::numeric_type::float64()
/// @brief 64-bit floating point type.

/// @fn callisto::framework::numeric_type::size()
/// @brief Return size in bytes of given type.
/// @return Size in bytes.

/// @fn callisto::framework::numeric_type::instance()
/// @brief Returns @see callisto::framework::numeric_type represents concrete type (int, float,
/// int64_t etc).
/// @tparam type Given type.
/// @return Type represents by @see callisto::framework::numeric_type

using uint8 = uint8_t;
using int8  = int8_t;

using uint16 = uint16_t;
using int16  = int16_t;

using uint32 = uint32_t;
using int32  = int32_t;

using uint64 = uint64_t;
using int64  = int64_t;

using float32 = float;
using float64 = double;

inline constexpr size_t numeric_type::size() const noexcept
{
    switch (_enum_data)
    {
        case inner::uint8 :
        case inner::int8 : return 1;

        case inner::uint16 :
        case inner::int16 : return 2;

        case inner::uint32 :
        case inner::int32 :
        case inner::float32 : return 4;

        case inner::uint64 :
        case inner::int64 :
        case inner::float64 : return 8;

        default : return 0;
    }
}

#define DECLARE_GET_TYPE_SPECIALIZATION(type)                                   \
    template<>                                                                  \
    inline constexpr numeric_type numeric_type::instance<type>() noexcept       \
    {                                                                           \
        return numeric_type::type();                                            \
    }                                                                           \
                                                                                \
    template<>                                                                  \
    inline constexpr numeric_type numeric_type::instance<const type>() noexcept \
    {                                                                           \
        return numeric_type::type();                                            \
    }

DECLARE_GET_TYPE_SPECIALIZATION(uint8);
DECLARE_GET_TYPE_SPECIALIZATION(int8);

DECLARE_GET_TYPE_SPECIALIZATION(uint16);
DECLARE_GET_TYPE_SPECIALIZATION(int16);

DECLARE_GET_TYPE_SPECIALIZATION(uint32);
DECLARE_GET_TYPE_SPECIALIZATION(int32);

DECLARE_GET_TYPE_SPECIALIZATION(uint64);
DECLARE_GET_TYPE_SPECIALIZATION(int64);

DECLARE_GET_TYPE_SPECIALIZATION(float32);
DECLARE_GET_TYPE_SPECIALIZATION(float64);

} // namespace callisto::framework
