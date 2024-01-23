#pragma once

// project
#include <callisto/framework/types/assert_traits.hpp>
#include <callisto/opencv.hpp>

#include "font_symbol_metrics.hpp"

namespace callisto::graphics
{

class font_symbol_data
{
    // data
    cv::Mat _bitmap;

    font_symbol_metrics _metrics;

public:
    // construct and destruct
    font_symbol_data();

    font_symbol_data(const font_symbol_data&) = delete;

    font_symbol_data(const font_symbol_metrics& metrics, const cv::Mat& bitmap);

    font_symbol_data(const font_symbol_metrics& metrics, cv::Mat&& bitmap);

    font_symbol_data(font_symbol_data&& info) = default;

    // methods
    font_symbol_data clone() const;

    // getters and setters
    font_symbol_metrics& get_metrics();

    const font_symbol_metrics& get_metrics() const;

    cv::Mat& get_bitmap();

    const cv::Mat& get_bitmap() const;

    // operators
    font_symbol_data& operator=(const font_symbol_data&) = delete;

    font_symbol_data& operator=(font_symbol_data&& info) = default;
};

CALLISTO_ASSERT_TRAIT_ONLY_MOVE(font_symbol_data);

} // namespace callisto::graphics