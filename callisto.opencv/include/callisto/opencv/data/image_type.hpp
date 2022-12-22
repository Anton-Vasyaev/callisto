#pragma once

#include <cstdint>

namespace callisto::opencv
{

enum class image_type : uint32_t
{
    unknown,
    rgb,
    rgba,
    bgr,
    bgra,
    grayscale,
    grayscale_alpha,
    channels_1,
    channels_2,
    channels_3,
    channels_4,
    channels_5,
    channels_6,
    channels_7,
    channels_8
};

inline constexpr const char* image_type_str(image_type type) noexcept
{
    switch (type)
    {
        case image_type::unknown : return "unknown";
        case image_type::rgb : return "rgb";
        case image_type::rgba : return "rgba";
        case image_type::bgr : return "bgr";
        case image_type::bgra : return "bgra";
        case image_type::grayscale : return "grayscale";
        case image_type::grayscale_alpha : return "grayscale_alpha";

        case image_type::channels_1 : return "channels_1";
        case image_type::channels_2 : return "channels_2";
        case image_type::channels_3 : return "channels_3";
        case image_type::channels_4 : return "channels_4";
        case image_type::channels_5 : return "channels_5";
        case image_type::channels_6 : return "channels_6";
        case image_type::channels_7 : return "channels_7";
        case image_type::channels_8 : return "channels_8";

        default : return nullptr;
    }
}

inline static constexpr image_type unspecified_image_type_from_channels(uint64_t channels)
{
    return (image_type)(int(image_type::channels_1) + channels - 1);
}

inline static constexpr int image_type_channels(image_type type) noexcept
{
    switch (type)
    {
        case image_type::grayscale :
        case image_type::channels_1 : return 1;

        case image_type::grayscale_alpha :
        case image_type::channels_2 : return 2;

        case image_type::rgb :
        case image_type::bgr :
        case image_type::channels_3 : return 3;

        case image_type::rgba :
        case image_type::bgra :
        case image_type::channels_4 : return 4;

        case image_type::channels_5 : return 5;
        case image_type::channels_6 : return 6;
        case image_type::channels_7 : return 7;
        case image_type::channels_8 : return 8;

        default : return int(type) - int(image_type::channels_1) + 1;
    }
}

} // namespace callisto::opencv