// test
#include <callisto/opencv/rw.hpp>
// std
#include <iostream>
// 3rd party
#include <boost/filesystem/fstream.hpp>
#include <gtest/gtest.h>
#include <callisto/framework/test/gtest.hpp>

namespace b_fs = boost::filesystem;
namespace c_cv = callisto::opencv;


TEST(opencv_auxiliary, read_write_utf8_test)
{
    auto img_w = 1600;
    auto img_h = 900;

    auto img_path = L"Изображение_漢字.png";
    auto mat      = cv::Mat(img_w, img_h, CV_8UC3);

    c_cv::imwrite(img_path, mat);

    auto read_img = c_cv::imread(img_path);

    ASSERT_EQ(read_img.cols, img_h);
    ASSERT_EQ(read_img.rows, img_w);
}