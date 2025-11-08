#pragma once

#include <callisto/math/primitives.hpp>
#include <callisto/math/operations.hpp>

namespace callisto::math
{

struct bbox2op
{
    template<typename type>
    static constexpr auto normalize(const bbox2<type>& box, const bbox2<type>& contour)
    {
        auto w = contour.width();
        auto h = contour.height();

        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        x1 = (x1 - contour.x1) / w;
        y1 = (y1 - contour.y1) / h;

        x2 = (x2 - contour.x1) / w;
        y2 = (y2 - contour.y1) / h;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<typename type>
    static constexpr auto reverse_normalize(const bbox2<type>& box, const bbox2<type>& contour)
    {
        auto contour_w = contour.width();
        auto contour_h = contour.height();

        auto x1 = box.x1 * contour_w + contour.x1;
        auto y1 = box.y1 * contour_h + contour.y1;

        auto x2 = box.x2 * contour_w + contour.x1;
        auto y2 = box.y2 * contour_h + contour.y1;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<typename type>
    static constexpr auto center(const bbox2<type>& box)
    {
        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        auto x_center = (x1 + x2) / 2;
        auto y_center = (y1 + y2) / 2;

        return point2<type>(x_center, y_center);
    }

    template<typename type>
    static constexpr auto scale(const bbox2<type>& box, size2<type> scale_size)
    {
        auto x_scale = scale_size.x;
        auto y_scale = scale_size.y;

        auto center_point = bbox2op::center(box);

        auto x1 = box.x1;
        auto y1 = box.y1;

        auto x2 = box.x2;
        auto y2 = box.y2;

        x1 = (x1 - center_point.x) * x_scale + center_point.x;
        y1 = (y1 - center_point.y) * y_scale + center_point.y;

        x2 = (x2 - center_point.x) * x_scale + center_point.x;
        y2 = (y2 - center_point.y) * y_scale + center_point.y;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<typename type>
    static constexpr auto intersection(const bbox2<type>& box1, const bbox2<type>& box2)
    {
        auto l = max_f(box1.x1, box2.x1);
        auto r = min_f(box1.x2, box2.x2);

        auto t = max_f(box1.y1, box2.y1);
        auto b = min_f(box1.y2, box2.y2);

        return bbox2<type>(l, t, r, b);
    }

    template<typename type>
    static constexpr double iom(const bbox2<type>& box1, const bbox2<type>& box2)
    {
        auto inter_box  = bbox2op::intersection(box1, box2);
        auto inter_area = static_cast<double>(inter_box.area());

        auto l = inter_box.x1;
        auto t = inter_box.y1;
        auto r = inter_box.x2;
        auto b = inter_box.y2;

        if (l >= r || t >= b)
        {
            return 0.0;
        }

        auto area1 = static_cast<double>(box1.area());
        auto area2 = static_cast<double>(box2.area());

        auto min_area = min_f(area1, area2);

        return inter_area / min_area;
    }

    template<typename type>
    static constexpr double iou(const bbox2<type>& box1, const bbox2<type>& box2)
    {
        auto inter_box  = bbox2op::intersection(box1, box2);
        auto inter_area = static_cast<double>(inter_box.area());

        auto l = inter_box.x1;
        auto t = inter_box.y1;
        auto r = inter_box.x2;
        auto b = inter_box.y2;

        if (l >= r || t >= b)
        {
            return 0.0;
        }

        auto area1 = static_cast<double>(box1.area());
        auto area2 = static_cast<double>(box2.area());

        auto union_area = area1 + area2 - inter_area;

        return inter_area / union_area;
    }

    template<typename type>
    static constexpr auto move(const bbox2<type>& box, const vector2<type>& move_vector)
    {
        auto x1 = box.x1 + move_vector.x;
        auto y1 = box.y1 + move_vector.y;

        auto x2 = box.x2 + move_vector.x;
        auto y2 = box.y2 + move_vector.y;

        return bbox2<type>(x1, y1, x2, y2);
    }

    template<typename type>
    static constexpr auto from_center(point2<type> center, size2<type> size)
    {
        auto x1 = center.x - size.width / 2.0;
        auto y1 = center.y - size.height / 2.0;

        auto x2 = center.x + size.width / 2.0;
        auto y2 = center.y + size.height / 2.0;

        return bbox2<type>(x1, y1, x2, y2);
    };

    template<typename type>
    static constexpr auto to_rectangle(const bbox2<type>& box)
    {
        return rectangle<type>(box.x1, box.x2, box.width(), box.height());
    }

    template<typename type>
    static constexpr auto from_rectangle(const rectangle<type>& rect)
    {
        auto x1 = rect.x;
        auto y1 = rect.y;

        auto w = rect.width;
        auto h = rect.height;

        auto x2 = x1 + w;
        auto y2 = y1 + h;

        return bbox2<type>(x1, y1, x2, y2);
    }
};

} // namespace callisto::math