#pragma once

// std
#include <vector>
// 3rd party
#include <opencv2/opencv.hpp>

// project
#include <callisto/math/primitives/alg_tuple2.hpp>
#include <callisto/math/primitives/alg_tuple3.hpp>
#include <callisto/math/primitives/line2.hpp>
#include <callisto/math/primitives/bbox2.hpp>

#include <callisto/opencv/auxiliary.hpp>

namespace callisto::opencv
{

/// @brief Draws bounding box on the image.
/// @param img        Given image.
/// @param p1         Coords of left-top point
/// @param p2         Coords of right-bottom point
/// @param color      Three color values in order: RGB.
/// @param thickness  Thickness of rectangle (in pixels).
/// @param line_type  Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
void draw_bbox_p(
    cv::Mat&                       img,
    const callisto::math::point2f& p1,
    const callisto::math::point2f& p2,
    const callisto::math::color3i& color,
    int                            thickness  = 1,
    int                            line_type  = cv::LINE_8,
    bool                           normalized = true
)
{
    namespace c_m = callisto::math;

    auto size = mat_size(img);

    c_m::point2f p1_t = p1;
    c_m::point2f p2_t = p2;
    if (normalized)
    {
        p1_t *= size.as<float>();
        p2_t *= size.as<float>();
    }

    auto p1i = p1_t.as<int32_t>();
    auto p2i = p2_t.as<int32_t>();

    auto clr_d = color.as<double>();

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
/// @param img Given image.
/// @param box Bounding box.
/// @param color Three color values in order: RGB.
/// @param thickness Thickness of bounding box in pixels.
/// @param line_type Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
void draw_bbox(
    cv::Mat&                       img,
    const callisto::math::bbox2f&  box,
    const callisto::math::color3i& color,
    int                            thickness  = 1,
    int                            line_type  = cv::LINE_8,
    bool                           normalized = true
)
{
    draw_bbox_p(img, box.left_top(), box.right_bottom(), color, thickness, line_type, normalized);
}

/// @brief Draws line on image.
/// @param img        Given image.
/// @param p1         First point of line.
/// @param p2         Second point of line.
/// @param color      Three color values in order: RGB.
/// @param thickness  Thickness of bounding box in pixels.
/// @param line_type  Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
void draw_line_p(
    cv::Mat&                       img,
    const callisto::math::point2f& p1,
    const callisto::math::point2f& p2,
    const callisto::math::color3i& color,
    int                            thickness  = 1,
    int                            line_type  = cv::LINE_8,
    bool                           normalized = true
)
{
    namespace c_m = callisto::math;

    auto size = mat_size(img);

    c_m::point2f p1_t = p1;
    c_m::point2f p2_t = p2;
    if (normalized)
    {
        p1_t *= size.as<float>();
        p2_t *= size.as<float>();
    }

    auto p1i = p1_t.as<int32_t>();
    auto p2i = p2_t.as<int32_t>();

    auto clr_d = color.as<double>();

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
/// @param img        Given image.
/// @param line       Line.
/// @param color      Three color values in order: RGB.
/// @param thickness  Thickness of bounding box in pixels.
/// @param line_type  Type of drawing line.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
void draw_line(
    cv::Mat&                       img,
    const callisto::math::line2f&  line,
    const callisto::math::color3i& color,
    int                            thickness  = 1,
    int                            line_type  = cv::LINE_8,
    bool                           normalized = true
)
{
    draw_line_p(img, line.first(), line.second(), color, thickness, line_type, normalized);
}

/// @brief Draws point on image.
/// @param img Given image.
/// @param point Coords of point.
/// @param color Three color values in order: RGB.
/// @param radius Radius of point.
/// @param normalized Flag indicating that the coordinates are given in normalized form (from 0.0
/// to 1.0)
void point(
    cv::Mat                        img,
    const callisto::math::point2f& point,
    const callisto::math::color3i& color,
    int                            radius     = 1,
    bool                           normalized = true
)
{
    namespace c_m = callisto::math;

    const int thickness = radius + 1;

    auto size = mat_size(img);

    auto point_t = point;
    if (normalized)
    {
        point_t *= size.as<float>();
    }

    auto p_i = point_t.as<int32_t>();

    auto clr_d = color.as<double>();

    cv::circle(img, { p_i.x, p_i.y }, radius, { clr_d.b, clr_d.g, clr_d.r }, thickness);
}

template<typename point_container_type>
void fill_polygon(
    cv::Mat&                       img,
    const point_container_type&    points,
    const callisto::math::color3i& color,
    int                            line_type  = cv::LINE_8,
    bool                           normalized = true
)
{
    auto size = mat_size(img).as<double>();

    std::vector<cv::Point> cv_points;
    cv_points.reserve(points.size());

    for (auto point : points)
    {
        auto p = point.as<double>();

        if (normalized) p *= size;

        cv_points.emplace_back(static_cast<int>(p.x), static_cast<int>(p.y));
    }

    auto* points_ptr      = cv_points.data();
    auto* const_points_pp = const_cast<const cv::Point**>(&points_ptr);

    auto        points_size = static_cast<int>(points.size());
    const auto* size_ptr    = &points_size;

    auto cv_color = cv::Scalar(color.b, color.g, color.r);

    cv::fillPoly(img, const_points_pp, size_ptr, 1, cv_color, line_type);
}

template<typename polygon_coords_container_type>
void draw_polygon(
    cv::Mat&                             image,
    const polygon_coords_container_type& poly_coords,
    callisto::math::color3i              color,
    int                                  thickness  = 1,
    int                                  line_type  = cv::LINE_8,
    bool                                 normalized = true
)
{
    auto prev_coord = poly_coords.front();

    auto first_coord = prev_coord;

    bool first_flag = true;
    for (auto& coord : poly_coords)
    {
        if (first_flag)
        {
            first_flag = false;
            continue;
        }

        draw_line_p(image, coord, prev_coord, color, thickness, line_type, normalized);

        prev_coord = coord;
    }

    draw_line_p(image, prev_coord, first_coord, color, thickness, line_type, normalized);
}

template<typename polygon_coords_container_type>
void draw_polyline(
    cv::Mat&                             image,
    const polygon_coords_container_type& poly_coords,
    callisto::math::color3i              color,
    int                                  thickness  = 1,
    int                                  line_type  = cv::LINE_8,
    bool                                 normalized = true
)
{
    auto prev_coord = poly_coords.front();

    auto first_coord = prev_coord;

    bool first_flag = true;
    for (auto& coord : poly_coords)
    {
        if (first_flag)
        {
            first_flag = false;
            continue;
        }

        draw_line_p(image, coord, prev_coord, color, thickness, line_type, normalized);

        prev_coord = coord;
    }
}

} // namespace callisto::opencv