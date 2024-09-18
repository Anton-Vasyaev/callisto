// parent header
#include <callisto/opencv/draw.hpp>

// std
#include <vector>
// project
#include <callisto/opencv/auxiliary.hpp>

namespace c_m = callisto::math;

namespace callisto::opencv
{

void draw_bbox_p(
    cv::Mat&                       img,
    const callisto::math::point2f& p1,
    const callisto::math::point2f& p2,
    const callisto::math::color3i& color,
    int                            thickness,
    int                            line_type,
    bool                           normalized
)
{
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

void draw_bbox(
    cv::Mat&                       img,
    const callisto::math::bbox2f&  box,
    const callisto::math::color3i& color,
    int                            thickness,
    int                            line_type,
    bool                           normalized
)
{
    draw_bbox_p(img, box.left_top(), box.right_bottom(), color, thickness, line_type, normalized);
}

void draw_line_p(
    cv::Mat&                       img,
    const callisto::math::point2f& p1,
    const callisto::math::point2f& p2,
    const callisto::math::color3i& color,
    int                            thickness,
    int                            line_type,
    bool                           normalized
)
{
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

void draw_line(
    cv::Mat&                       img,
    const callisto::math::line2f&  line,
    const callisto::math::color3i& color,
    int                            thickness,
    int                            line_type,
    bool                           normalized
)
{
    draw_line_p(img, line.first(), line.second(), color, thickness, line_type, normalized);
}

void draw_circle(
    cv::Mat&                       img,
    const callisto::math::point2f& point,
    const callisto::math::color3i& color,
    int                            radius,
    bool                           normalized
)
{
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

} // namespace callisto::opencv