#pragma once

// 3rd party
#include <opencv2/opencv.hpp>
#include <callisto/framework/native/numeric_type.hpp>
#include <callisto/framework/exception.hpp>
#include <callisto/framework/string/build_string.hpp>
// project
#include <callisto/opencv/auxiliary.hpp>

namespace callisto::opencv
{

namespace
{
namespace c_f = callisto::framework;
}

struct validation
{

    template<typename string_type_1 = const char*, typename string_type_2 = const char*>
    inline static void is_equal_dimensions(
        const cv::Mat&       mat_1,
        const cv::Mat&       mat_2,
        const string_type_1& argument_name_1 = "m1",
        const string_type_2& argument_name_2 = "m2"
    )
    {
        auto w1 = mat_1.cols;
        auto h1 = mat_1.rows;
        auto c1 = mat_channels(mat_1);

        auto w2 = mat_2.cols;
        auto h2 = mat_2.rows;
        auto c2 = mat_channels(mat_2);

        if (w1 != w2 || h1 != h2 || c1 != c2)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(c_f::_bs(
                "dimensions of \'",
                argument_name_1,
                "\' and \'",
                argument_name_2,
                "\' not equals: ",
                "(",
                w1,
                " x ",
                h1,
                " x ",
                c1,
                ") != (",
                w2,
                " x ",
                h2,
                " x ",
                c2,
                "). (width x height x channels)."
            ));
        }
    }

    template<typename string_type_1 = const char*, typename string_type_2 = const char*>
    inline static void is_equal_sizes(
        const cv::Mat&       mat_1,
        const cv::Mat&       mat_2,
        const string_type_1& argument_name_1 = "m1",
        const string_type_2& argument_name_2 = "m2"
    )
    {
        auto w1 = mat_1.cols;
        auto h1 = mat_1.rows;

        auto w2 = mat_2.cols;
        auto h2 = mat_2.rows;

        if (w1 != w2 || h1 != h2)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(c_f::_bs(
                "sizes of \'",
                argument_name_1,
                "\' and \'",
                argument_name_2,
                "\' not equals: ",
                "(",
                w1,
                " x ",
                h1,
                ") != (",
                w2,
                " x ",
                h2,
                "). (width x height)"
            ));
        }
    }

    template<typename string_type = const char*>
    inline static void
    is_equal_channels(const cv::Mat& mat, int channels, const string_type& argument_name = "m")
    {
        auto mat_c = mat_channels(mat);

        if (channels != mat_c)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(
                c_f::_bs("channels of mat \'", argument_name, "\' != ", channels, ": ", mat_c, ".")
            );
        }
    }

    template<typename string_type_1 = const char*, typename string_type_2 = const char*>
    inline static void is_equal_channels(
        const cv::Mat&       mat1,
        const cv::Mat&       mat2,
        const string_type_1& argument_name_1 = "m1",
        const string_type_2& argument_name_2 = "m2"
    )
    {
        auto mat1_channels = mat_channels(mat1);
        auto mat2_channels = mat_channels(mat2);

        if (mat1_channels != mat2_channels)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(c_f::_bs(
                "channels in mats \'",
                argument_name_1,
                "\' and \'",
                argument_name_2,
                "\' not equal: ",
                mat1_channels,
                " != ",
                mat2_channels,
                "."
            ));
        }
    }

    template<typename string_type = const char*>
    static void is_numeric_type(
        const cv::Mat&     mat,
        c_f::numeric_type  num_type,
        const string_type& argument_name = "m"
    )
    {
        auto mat_num_type = mat_numeric_type(mat);

        if (mat_num_type != num_type)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(c_f::_bs(
                "numeric type of mat \'",
                argument_name,
                "\' != ",
                c_f::numeric_type_str(num_type),
                ": ",
                c_f::numeric_type_str(mat_num_type),
                "."
            ));
        }
    }

    template<typename string_type_1 = const char*, typename string_type_2 = const char*>
    static void is_larger_size(
        const cv::Mat&       mat1,
        const cv::Mat&       mat2,
        const string_type_1& argument_name_1 = "m1",
        const string_type_2& argument_name_2 = "m2"
    )
    {
        if (mat1.cols < mat2.cols || mat1.rows < mat2.rows)
        {
            CALLISTO_THROW_EXCEPTION(c_f::runtime_exception()) << c_f::error_tag_message(c_f::_bs(
                "size of \'",
                argument_name_1,
                "\' (",
                mat1.cols,
                " x ",
                mat1.rows,
                ") is not larger than \'",
                argument_name_2,
                "\' (",
                mat2.cols,
                " x ",
                mat2.rows,
                ")."
            ));
        }
    }
};

} // namespace callisto::opencv