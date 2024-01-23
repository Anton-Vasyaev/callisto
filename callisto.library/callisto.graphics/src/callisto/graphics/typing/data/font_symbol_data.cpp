// parent header
#include <callisto/graphics/typing/data/font_symbol_data.hpp>

namespace callisto::graphics
{
#pragma region construct_and_destruct

font_symbol_data::font_symbol_data() {}

font_symbol_data::font_symbol_data(const font_symbol_metrics& metrics, const cv::Mat& bitmap)
{
    _metrics = metrics;
    _bitmap  = bitmap;
}

font_symbol_data::font_symbol_data(const font_symbol_metrics& metrics, cv::Mat&& bitmap)
{
    _metrics = metrics;
    _bitmap  = std::move(bitmap);
}

#pragma endregion

#pragma region methods

font_symbol_data font_symbol_data::clone() const { return font_symbol_data(_metrics, _bitmap); }

#pragma endregion

#pragma region getters_and_setters

font_symbol_metrics& font_symbol_data::get_metrics() { return _metrics; }

const font_symbol_metrics& font_symbol_data::get_metrics() const { return _metrics; }

cv::Mat& font_symbol_data::get_bitmap() { return _bitmap; }

const cv::Mat& font_symbol_data::get_bitmap() const { return _bitmap; }

#pragma endregion
} // namespace callisto::graphics