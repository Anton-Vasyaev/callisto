#pragma once

// 3rd party
#include <opencv2/opencv.hpp>

#include <callisto/framework/exception.hpp>
// project
#include "data/image_type.hpp"
#include "auxiliary.hpp"

namespace callisto::opencv
{

class mat_holder
{
    cv::Mat mat_data;

    image_type img_type;

public:
    // deleted functions
    mat_holder(const mat_holder& mat) = delete;

    // construct and destruct
    mat_holder() { img_type = image_type::unknown; }

    mat_holder(mat_holder&& holder)
    {
        this->mat_data = std::move(holder.mat_data);
        this->img_type = holder.img_type;
    }

    mat_holder(cv::Mat& mat, image_type img_type)
    {
        this->mat_data = mat;
        this->img_type = img_type;
    }

    mat_holder(cv::Mat&& mat, image_type img_type)
    {
        this->mat_data = std::move(mat);
        this->img_type = img_type;
    }

    // methods
    inline mat_holder copy() const
    {
        auto holder     = mat_holder();
        holder.img_type = this->img_type;
        this->mat_data.copyTo(holder.mat());

        return holder;
    }

    inline void validate(const char* function_name = nullptr) const
    {
        match_image_type(this->mat_data, this->img_type, "mat_holder::validate");
    }

    // getters and setters
    inline void set_mat(cv::Mat& mat) { this->mat_data = mat; }

    inline void set_mat(cv::Mat&& mat) { this->mat_data = std::move(mat); }

    inline cv::Mat& mat() { return this->mat_data; }

    inline const cv::Mat& mat() const { return this->mat_data; }

    inline void set_image_type(image_type img_type) { this->img_type = img_type; }

    inline image_type get_image_type() const { return this->img_type; }
};

} // namespace callisto::opencv