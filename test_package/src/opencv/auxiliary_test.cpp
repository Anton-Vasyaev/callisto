#ifndef CALLISTO_OPENCV_DISABLE

    // test
    #include <callisto/opencv/auxiliary.hpp>
    // std
    #include <iostream>
    // 3rd party
    #include <gtest/gtest.h>
    #include <callisto/framework/test/gtest.hpp>

namespace c_f = callisto::framework;

namespace c_cv = callisto::opencv;

template<typename value_type, typename... pack_type>
constexpr bool equal_values(const value_type& value, const pack_type&&... args)
{
    auto equal_status = true;

    ((equal_status &= (args == value)), ...);

    return equal_status;
}

TEST(opencv_auxiliary, auxiliary_test_1)
{
    auto mat_type_1 = c_cv::make_type(c_f::numeric_type::uint8, c_cv::image_type::bgr);
    auto mat_type_2 = c_cv::make_type(c_f::numeric_type::int16, 3);
    auto mat_type_3 = c_cv::make_type(CV_32F, 3);
    auto mat_type_4 = c_cv::make_type(c_f::numeric_type::int32, c_cv::image_type::rgb);

    auto equal_status = equal_values(
        c_cv::type_channels(mat_type_1),
        c_cv::type_channels(mat_type_2),
        c_cv::type_channels(mat_type_3),
        c_cv::type_channels(mat_type_4)
    );

    ASSERT_EQ(true, equal_status);
}

TEST(opencv_auxiliary, auxiliary_test_2)
{
    auto mat_type_1 = c_cv::make_type(c_f::numeric_type::float32, c_cv::image_type::bgr);
    auto mat_type_2 = c_cv::make_type(CV_32F, 3);
    auto mat_type_3 = c_cv::make_type(c_f::numeric_type::float32, c_cv::image_type::grayscale);
    auto mat_type_4 = c_cv::make_type(CV_32F, 1);

    auto equal_status = equal_values(
        c_cv::cv2numeric(mat_type_1),
        c_cv::cv2numeric(mat_type_2),
        c_cv::cv2numeric(mat_type_3),
        c_cv::cv2numeric(mat_type_4)
    );

    ASSERT_EQ(true, equal_status);
}

#endif