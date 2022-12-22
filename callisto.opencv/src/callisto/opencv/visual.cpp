// parent header
#include <callisto/opencv/visual.hpp>
// std
#include <cstdlib>

namespace callisto::opencv
{

int imshow(const cv::String& winname, cv::InputArray mat, int wait_ms, bool catch_exit)
{
    cv::imshow(winname, mat);
    auto key = cv::waitKey(wait_ms);
    if (key == 27) { std::exit(0); }

    return key;
}

} // namespace callisto::opencv