#pragma once

// std
#include <cstddef>
#include <cstdint>
#include <string_view>
// project

using float32_t = float;
using float64_t = double;

namespace callisto::framework
{

/// @brief Type of native basic numeric type.
enum class numeric_type
{
    /// @brief Unknown type.
    unknown,

    /// @brief 8-bit unsigned type.
    uint8,

    /// @brief 8-bit signed type.
    int8,

    /// @brief 16-bit unsigned type.
    uint16,

    /// @brief 16-bit signed type.
    int16,

    /// @brief 32-bit unsigned type.
    uint32,

    /// @brief 32-bit signed type.
    int32,

    /// @brief 64-bit unsigned type.
    uint64,

    /// @brief 64-bit nsigned type.
    int64,

    /// @brief 32-bit floating point type.
    float32,

    /// @brief 64-bit floating point type.
    float64
};

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

/// @brief Returns size in bytes of given type.
/// @param num_type numeric type.
/// @return Size of numeric type in bytes.
inline constexpr int numeric_type_size(numeric_type num_type) noexcept
{
    switch (num_type)
    {
        case numeric_type::uint8 :
        case numeric_type::int8 : return 1;

        case numeric_type::uint16 :
        case numeric_type::int16 : return 2;

        case numeric_type::uint32 :
        case numeric_type::int32 :
        case numeric_type::float32 : return 4;

        case numeric_type::uint64 :
        case numeric_type::int64 :
        case numeric_type::float64 : return 8;

        default : return 0;
    }
}

inline constexpr const char* numeric_type_str(numeric_type num_type) noexcept
{
    switch (num_type)
    {
        case numeric_type::uint8 : return "uint8";
        case numeric_type::int8 : return "int8";

        case numeric_type::uint16 : return "uint16";
        case numeric_type::int16 : return "int16";

        case numeric_type::uint32 : return "uint32";
        case numeric_type::int32 : return "int32";

        case numeric_type::uint64 : return "uint64";
        case numeric_type::int64 : return "int64";

        case numeric_type::float32 : return "float32";
        case numeric_type::float64 : return "float64";

        default : return "unknown";
    }
}

template<typename type>
inline constexpr numeric_type numeric_type_instance() noexcept;

#define DECLARE_GET_TYPE_SPECIALIZATION(type)                                  \
    template<>                                                                 \
    inline constexpr numeric_type numeric_type_instance<type>() noexcept       \
    {                                                                          \
        return numeric_type::type;                                             \
    }                                                                          \
                                                                               \
    template<>                                                                 \
    inline constexpr numeric_type numeric_type_instance<const type>() noexcept \
    {                                                                          \
        return numeric_type::type;                                             \
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
