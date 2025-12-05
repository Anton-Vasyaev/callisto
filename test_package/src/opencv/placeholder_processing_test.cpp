// test
#include <callisto/opencv.hpp>
// std
#include <iostream>
// 3rd party
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace c_cv = callisto::opencv;
namespace c_f  = callisto::framework;

TEST(opencv_auxiliary, placeholder_processing_test)
{
    auto img = cv::Mat(
        1000, 
        2000, 
        c_cv::make_type(
            c_f::numeric_type::uint8,
            c_cv::image_type::grayscale
        )
    );
}
