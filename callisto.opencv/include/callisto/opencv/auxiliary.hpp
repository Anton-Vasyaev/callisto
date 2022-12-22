#pragma once

// 3rd party
#include <opencv2/opencv.hpp>

#include <callisto/framework/concepts.hpp>
#include <callisto/framework/native/numeric_type.hpp>
#include <callisto/framework/string.hpp>
#include <callisto/framework/exception.hpp>

#include <callisto/math/primitives/alg_tuple2.hpp>

// project
#include "data/image_type.hpp"

namespace callisto::opencv
{

namespace
{
namespace c_f = callisto::framework;
namespace c_m = callisto::math;
}

/// @brief Returns base CV type of given CV type. For example, for CV_32FC3 return CV_32F.
/// @param cv_type CV type.
/// @return Base CV type.
inline constexpr int base_type(int cv_type);

/// @brief Returns base CV type of givet @see cv::Mat.
/// @param mat @see cv::Mat.
/// @return Base CV Type.
inline int base_type(const cv::Mat& mat);

/// @brief Returns number of channels for CV type.
/// @param cv_type CV type.
/// @return Number of channels.
inline constexpr int type_channels(int cv_type);

/// @brief Returns number of channels for CV type.
/// @param cv_type CV type.
/// @return Number of channels.
inline int mat_channels(const cv::Mat& mat);

/// @brief Returns numeric type represent by mat type.
/// @param cv_type Mat type.
/// @return Numeric type.
constexpr c_f::numeric_type cv2numeric(int cv_type);

/// @brief Returns numeric type of mat.
/// @param mat Given mat.
/// @return Numeric type of mat.
inline c_f::numeric_type mat_numeric_type(const cv::Mat& mat);

/// @brief Converts numeric type for base mat type.
/// @param num_type Numeric type.
/// @return Base mat type.
constexpr int numeric2cv(c_f::numeric_type num_type);

/// @brief Constructs CV type from base type and number of channels.
/// @param base_type Base CV type.
/// @param channels  Number of channels
/// @return Constructed CV type.
inline constexpr int make_type(int base_type, int channels);

/// @brief Constructs CV type from base type and image type..
/// @param base_type Base CV type.
/// @param img_type  Image type.
/// @return Constructed CV type.
inline constexpr int make_type(int base_type, image_type img_type);

/// @brief Constructs CV type from numeric type and number of channels.
/// @param num_type Numeric type.
/// @param channels Number of channels.
/// @return Constructed CV type.
constexpr int make_type(c_f::numeric_type num_type, int channels);

/// @brief Constructs CV type from numeric type and image type.
/// @param num_type Numeric type.
/// @param img_type Image type.
/// @return Constructed CV type.
inline constexpr int make_type(c_f::numeric_type num_type, image_type img_type);

/// @brief Matches mat and image type. If number of channels of mat and number of channels of image
/// type not matched, throws exception.
/// @param mat           Mat
/// @param img_type      Image type.
/// @param function_name Name of function, where call matching.
void match_image_type(
    const cv::Mat& mat,
    image_type     img_type,
    const char*    function_name = nullptr
);

/// @brief Returns default image type for mat.
/// @param mat Mat.
/// @return Default image type.
image_type default_image_type(const cv::Mat& mat);

/// @brief Converts mat by numeric type.
/// @param src Source mat.
/// @param dst Destination mat.
/// @param num_type Numeric type.
inline void convert(const cv::Mat& src, cv::Mat& dst, c_f::numeric_type num_type, double alpha = 1.0, double beta = 0.0);

/// @brief Converts mat bye basic arithmetic type.
/// @tparam type Basic arithmetic type.
/// @param src Source mat.
/// @param dst Destination mat.
template<c_f::concept_arithmetic type>
inline void convert(const cv::Mat& src, cv::Mat& dst, double alpha = 1.0, double beta = 0.0);

/// @brief Returns size of mat.
/// @param src Given mat.
/// @return Size of mat.
inline c_m::size2i mat_size(const cv::Mat& src);

/// @brief Returns stride of mat.
/// @param src Given mat.
/// @return Size of mat.
inline size_t mat_stride(const cv::Mat& src);


#pragma region realisation

inline constexpr int base_type(int cv_type)
{
    if (cv_type < 0 || cv_type >= 64) return -1;

    return cv_type % 8;
}

inline int base_type(const cv::Mat& mat)
{
    return base_type(mat.type());
}


inline constexpr int type_channels(int cv_type) { return cv_type / 8 + 1; }

inline int mat_channels(const cv::Mat& mat)
{
    return type_channels(mat.type());
}

constexpr c_f::numeric_type cv2numeric(int cv_type)
{
    auto type = base_type(cv_type);

    switch (type)
    {
        case CV_8U : return c_f::numeric_type::uint8();
        case CV_8S : return c_f::numeric_type::int8();
        case CV_16U : return c_f::numeric_type::uint16();
        case CV_16S : return c_f::numeric_type::int16();
        case CV_32S : return c_f::numeric_type::int32();
        case CV_32F : return c_f::numeric_type::float32();
        case CV_64F : return c_f::numeric_type::float64();
        default : return c_f::numeric_type::unknown();
    }
}

inline c_f::numeric_type mat_numeric_type(const cv::Mat& mat)
{
    return cv2numeric(mat.type());
}

constexpr int numeric2cv(c_f::numeric_type num_type)
{
    switch (num_type.get_data())
    {
        case c_f::numeric_type::inner::uint8 : return CV_8U;
        case c_f::numeric_type::inner::int8 : return CV_8S;
        case c_f::numeric_type::inner::uint16 : return CV_16U;
        case c_f::numeric_type::inner::int16 : return CV_16S;
        case c_f::numeric_type::inner::int32 : return CV_32S;
        case c_f::numeric_type::inner::float32 : return CV_32F;
        case c_f::numeric_type::inner::float64 : return CV_64F;
        default : return -1;
    }
}

inline constexpr int make_type(int base_type, int channels)
{
    return base_type + 8 * (channels - 1);
}

inline constexpr int make_type(int base_type, image_type img_type)
{
    return make_type(base_type, image_type_channels(img_type));
}

constexpr int make_type(c_f::numeric_type num_type, int channels)
{
    if (channels > 8 || channels <= 0)
    {
        throw c_f::argument_exception()
            << c_f::error_tag_message("failed to make_type, reason: channels > 8 or channels <= 0");
    }

    auto base_type = numeric2cv(num_type);
    if (base_type == -1)
    {
        throw c_f::argument_exception() << c_f::error_tag_message(c_f::_bs(
            "failed to make_type, not valid type for create cv::Mat:",
            num_type.str(),
            ", code:",
            static_cast<int>(num_type)
        ));
    }

    return make_type(base_type, channels);
}

inline constexpr int make_type(c_f::numeric_type num_type, image_type img_type)
{
    return make_type(num_type, image_type_channels(img_type));
}

inline void convert(const cv::Mat& src, cv::Mat& dst, c_f::numeric_type num_type, double alpha, double beta)
{
    auto channels        = type_channels(src.type());
    auto convert_cv_type = make_type(num_type, channels);

    src.convertTo(dst, convert_cv_type, alpha, beta);
}


template<c_f::concept_arithmetic type>
inline void convert(const cv::Mat& src, cv::Mat& dst, double alpha, double beta)
{
    return convert(src, dst, c_f::numeric_type::instance<type>());
}


inline c_m::size2i mat_size(const cv::Mat& src)
{
    return c_m::size2i(src.cols, src.rows);
}

inline size_t mat_stride(const cv::Mat& src)
{
    return static_cast<size_t>(src.step);
}

#pragma endregion

} // namespace callisto::opencv