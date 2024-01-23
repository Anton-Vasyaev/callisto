#pragma once

// std
#include <vector>
// 3rd party
#include <opencv2/opencv.hpp>

#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/math/primitives/alg_tuple3.hpp>
#include <callisto/math/primitives/line2.hpp>
#include <callisto/math/primitives/bbox2.hpp>

namespace callisto::opencv
{

namespace
{
namespace c_m = callisto::math;
}

/// @brief Draws rectangle on the image.
/// @tparam value_type_1 Value type of left-top point.
/// @tparam value_type_2 Value type of right-bottom point.
/// @param img        Given image.
/// @param p1         Coords of left-top point
/// @param p2         Coords of right-bottom point
/// @param color      Three color values in order: RGB.
/// @param thickness  Thickness of rectangle (in pixels).
/// @param line_type  Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
template<typename value_type_1, typename value_type_2>
void draw_rectangle(
    cv::Mat&                  img,
    c_m::point2<value_type_1> p1,
    c_m::point2<value_type_2> p2,
    c_m::color3i              color,
    int                       thickness  = 1,
    int                       line_type  = cv::LINE_8,
    bool                      normalized = true
)
{
    auto size = mat_size(img);
    if (normalized)
    {
        p1 *= size;
        p2 *= size;
    }

    auto p1i = c_m::point2i(p1);
    auto p2i = c_m::point2i(p2);

    auto clr_d = c_m::color3d(color);

    cv::rectangle(
        img,
        { p1i.x, p1i.y },
        { p2i.x, p2i.y },
        { clr_d.b, clr_d.g, clr_d.r },
        thickness,
        line_type
    );
}

/// @brief Draws bounding box on the image.
/// @tparam value_type Value type of bounding box.
/// @param img Given image.
/// @param box Bounding box.
/// @param color Three color values in order: RGB.
/// @param thickness Thickness of bounding box in pixels.
/// @param line_type Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
template<typename value_type>
void draw_bbox(
    cv::Mat&                      img,
    const c_m::bbox2<value_type>& box,
    c_m::color3i                  color,
    int                           thickness  = 1,
    int                           line_type  = cv::LINE_8,
    bool                          normalized = true
)
{
    draw_rectangle(
        img,
        box.left_top(),
        box.right_bottom(),
        color,
        thickness,
        line_type,
        normalized
    );
}

/// @brief Draws line on image.
/// @tparam value_type_1 Value type of first line point.
/// @tparam value_type_2 Value type of second line point.
/// @param img        Given image.
/// @param p1         First point of line.
/// @param p2         Second point of line.
/// @param color      Three color values in order: RGB.
/// @param thickness  Thickness of bounding box in pixels.
/// @param line_type  Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
template<typename value_type_1, typename value_type_2>
void draw_line(
    cv::Mat&                  img,
    c_m::point2<value_type_1> p1,
    c_m::point2<value_type_2> p2,
    c_m::color3i              color,
    int                       thickness  = 1,
    int                       line_type  = cv::LINE_8,
    bool                      normalized = true
)
{
    auto size = mat_size(img);
    if (normalized)
    {
        p1 *= size;
        p2 *= size;
    }

    auto p1i = c_m::point2i(p1);
    auto p2i = c_m::point2i(p2);

    auto clr_d = c_m::color3d(color);

    cv::line(
        img,
        { p1i.x, p1i.y },
        { p2i.x, p2i.y },
        { clr_d.b, clr_d.g, clr_d.r },
        thickness,
        line_type
    );
}

/// @brief Draws line on image.
/// @tparam value_type Value type of line.
/// @param img        Given image.
/// @param line       Line.
/// @param color      Three color values in order: RGB.
/// @param thickness  Thickness of bounding box in pixels.
/// @param line_type  Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
template<typename value_type>
void draw_line(
    cv::Mat&               img,
    c_m::line2<value_type> line,
    c_m::color3i           color,
    int                    thickness  = 1,
    int                    line_type  = cv::LINE_8,
    bool                   normalized = true
)
{
    draw_line(img, line.first(), line.second(), color, thickness, line_type, normalized);
}

/// @brief Draws point on image.
/// @tparam value_type Value type of point coords.
/// @param img Given image.
/// @param point Coords of point.
/// @param color Three color values in order: RGB.
/// @param radius Radius of point.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
template<typename value_type>
void point(
    cv::Mat                 img,
    c_m::point2<value_type> point,
    c_m::color3i            color,
    int                     radius     = 1,
    bool                    normalized = true
)
{
    int thickness = radius + 1;

    auto size = mat_size(img);
    if (normalized)
    {
        point *= size;
    }

    auto p_i = c_m::point2i(point);

    auto clr_d = c_m::color3d(color);

    cv::circle(img, { p_i.x, p_i.y }, radius, { clr_d.b, clr_d.g, clr_d.r }, thickness);
}

template<typename point_container_type>
void fill_polygon(
    cv::Mat&                    img,
    const point_container_type& points,
    c_m::color3i                color,
    int                         line_type  = cv::LINE_8,
    bool                        normalized = true
)
{
    auto size = mat_size(img);

    std::vector<cv::Point> cv_points;
    cv_points.reserve(points.size());

    for (auto point : points)
    {
        auto p = c_m::point2d(point);

        if (normalized) p *= size;

        cv_points.emplace_back((int)p.x, (int)p.y);
    }

    auto points_ptr      = cv_points.data();
    auto points_pp       = &points_ptr;
    auto const_points_pp = (const cv::Point**)(points_pp);

    auto points_size = (int)points.size();
    auto size_ptr    = (const int*)(&points_size);

    auto cv_color = cv::Scalar(color.b, color.g, color.r);

    cv::fillPoly(img, const_points_pp, size_ptr, 1, cv_color, line_type);
}

} // namespace callisto::opencv