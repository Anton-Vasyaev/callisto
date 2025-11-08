// parent header
#include <callisto/opencv/visual.hpp>
// std
#include <cstdlib>

// project

namespace callisto::opencv
{

int imshow(const cv::String& winname, cv::InputArray mat, int wait_ms)
{
    cv::imshow(winname, mat);
    auto key = cv::waitKey(wait_ms);

    return key;
}
} // namespace callisto::opencv