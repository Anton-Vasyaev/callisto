#pragma once

// 3rd party
#include <opencv2/opencv.hpp>


namespace callisto::opencv
{

int imshow(const cv::String& winname, cv::InputArray mat, int wait_ms = 0, bool catch_exit = true);

}