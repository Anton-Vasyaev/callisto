// parent header
#include <callisto/opencv/visual.hpp>
// std
#include <cstdlib>
// project
#include <callisto/framework/exception/exit_exception.hpp>

namespace callisto::opencv
{

int imshow(const cv::String& winname, cv::InputArray mat, int wait_ms)
{
    namespace c_f = callisto::framework;

    cv::imshow(winname, mat);
    auto key = cv::waitKey(wait_ms);

    return key;
}
} // namespace callisto::opencv