// test
#include <callisto/framework/configuration/object_enum.hpp>
// std
#include <string>
// 3rd party
#include <gtest/gtest.h>
// project
#include <callisto/framework/string.hpp>

namespace c_f = callisto::framework;

#define IMAGE_TYPE_FUNCTIONS constexpr int get_channels() const noexcept;

namespace imaging
{

CALLISTO_DEFINE_OBJECT_ENUM(
    image_type,
    IMAGE_TYPE_FUNCTIONS,
    (unknown),
    (rgb),
    (bgr),
    (rgba),
    (bgra),
    (gray, 750),
    (hsv)
);

} // namespace imaging

constexpr int imaging::image_type::get_channels() const noexcept
{
    switch (_enum_data)
    {
        case inner::gray : return 1;
        case inner::rgb :
        case inner::bgr :
        case inner::hsv : return 3;
        case inner::rgba :
        case inner::bgra : return 4;
        default : return 0;
    }
}

/// Example doxygen commenting for macros generated class.

/// @struct imaging::image_type
/// @brief Object enum of image type.

/// @fn imaging::image_type::get_channels()
/// @brief Return number of channels for the given type.

/// @fn imaging::image_type::rgb()
/// @brief Color 3-channels image type in order (Red, Green, Blue).

/// @fn imaging::image_type::bgr()
/// @brief Color 3-channel image type in order (Blue, Green, Red).

/// @fn imaging::image_type::rgba()
/// @brief Color 4-channels image type in order (Red, Green, Blue, Alpha).

/// @fn imaging::image_type::bgra()
/// @brief Color 4-channels image_type in order (Blue, Green, Red, Alpha).

/// @fn imaging::image_type::gray()
/// @brief Grayscale 1-channels image type.

/// @fn imaging::image_type::hsv()
/// @brief Color 3-channels image type in order (Hue, Saturation, Value).

TEST(framework_configuration, object_enum)
{
    auto unknown_type = static_cast<imaging::image_type>(243);

    auto grayscale_type = imaging::image_type::gray();

    ASSERT_STREQ(imaging::image_type::rgb().str(), "rgb");
    ASSERT_EQ(imaging::image_type::hsv().get_channels(), 3);
    ASSERT_EQ(imaging::image_type::gray().get_channels(), 1);
    ASSERT_EQ(unknown_type.get_channels(), 0);
    ASSERT_STREQ(unknown_type.str(), "");
    ASSERT_EQ(static_cast<int>(grayscale_type), 750);
    ASSERT_EQ(grayscale_type, imaging::image_type::gray());

    auto enum_data = grayscale_type.get_data();
    auto gray_str  = std::string("");
    switch (enum_data)
    {
        case imaging::image_type::inner::bgr : gray_str = "BGR"; break;
        case imaging::image_type::inner::rgba : gray_str = "RGBA"; break;
        case imaging::image_type::inner::gray : gray_str = "GRAY"; break;
        default : gray_str = "DEFAULT";
    }
    ASSERT_EQ(gray_str, "GRAY");
}