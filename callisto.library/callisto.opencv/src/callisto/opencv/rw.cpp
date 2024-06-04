// parent header
#include <callisto/opencv/rw.hpp>

namespace callisto::opencv
{

cv::Mat imdecode(const void* buffer_ptr, int buffer_size, int flags)
{
    auto mat_buffer = cv::Mat(1, buffer_size, CV_8UC1, const_cast<void*>(buffer_ptr));

    return cv::imdecode(mat_buffer, flags);
}

} // namespace callisto::opencv