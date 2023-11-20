#pragma once
// std
#include <vector>
#include <fstream>
// 3rd party
#include <boost/current_function.hpp>
#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>

#include <callisto/framework/exception.hpp>
#include <callisto/framework/ios/fstream_aux.hpp>
#include <callisto/framework/string.hpp>
#include <callisto/framework/exception.hpp>
#include <callisto/framework/native/numeric_type.hpp>
// project
#include "auxiliary.hpp"
#include "exception.hpp"

namespace callisto::opencv
{

namespace
{
namespace b_fs = boost::filesystem;
namespace c_f  = callisto::framework;
} // namespace

cv::Mat imdecode(const void* buffer_ptr, size_t buffer_size, int flags = cv::IMREAD_UNCHANGED);

std::vector<uint8_t>
imencode(cv::Mat img, const char* ext, const std::vector<int>& params = std::vector<int>());

template<typename path_type>
cv::Mat imread(path_type* path, int flags = cv::IMREAD_UNCHANGED)
{
    b_fs::ifstream file_handler(path, std::ios::binary);

    if (!file_handler.is_open())
    {
        CALLISTO_THROW_EXCEPTION(read_write_exception()) << c_f::error_tag_message_w(
            c_f::_wbs(L"imread failed. img on path \'", path, L"\' not opened.")
        );
    }

    auto file_size = b_fs::file_size(path);

    auto file_data = std::vector<uint8_t>(file_size);

    file_handler.read(reinterpret_cast<char*>(file_data.data()), file_size);

    return imdecode(file_data.data(), file_size, flags);
}

template<typename path_type>
cv::Mat imread(path_type&& path, int flags = cv::IMREAD_UNCHANGED)
{
    return imread(path.c_str(), flags);
}

template<typename path_type>
void imwrite(path_type* path, const cv::Mat& img)
{
    b_fs::ofstream file_handler(path, std::ios::binary);

    if (!file_handler.is_open())
    {
        CALLISTO_THROW_EXCEPTION(read_write_exception()) << c_f::error_tag_message_w(
            c_f::_wbs(L"imwrite failed. file handler on path \'", path, L"\' not opened.")
        );
    }

    auto ext = boost::filesystem::path(path).extension().string();

    auto mat_type = img.type();
    auto num_type = cv2numeric(mat_type);
    auto channels = type_channels(mat_type);

    std::vector<uint8_t> encoded_data;
    auto reserve_size = img.cols * img.rows * img.channels() * c_f::numeric_type_size(num_type);
    encoded_data.reserve(reserve_size);

    cv::imencode(ext, img, encoded_data);

    file_handler.write((const char*)encoded_data.data(), encoded_data.size());
}

template<typename path_type>
void imwrite(path_type&& path, const cv::Mat& img)
{
    imwrite(path.c_str(), img);
}

} // namespace callisto::opencv