// std
#include <iostream>
#include <memory>
#include <codecvt>
// 3rd party
#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/concepts/core.hpp>

#include <callisto/reflection/json_reading_reflector.hpp>
#include <callisto/reflection/streaming_reflector.hpp>

#include "string_auxiliary_can.hpp"

#include <callisto/framework/types/type_traits/std_classes.hpp>

struct point3d
{
    float x;
    float y;
    float z;

    point3d() = default;
};

namespace callisto::framework
{
template<>
struct custom_reflection<point3d>
{
    static constexpr bool exist = true;

    point3d& data;

    explicit custom_reflection(point3d& data) : data(data) {}

    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        reflection.reflect(data.x, L"x");
        reflection.reflect(data.y, L"y");
        reflection.reflect(data.z, L"z");
    }
};
} // namespace callisto::framework

struct patterns_params
{
    // data
    std::wstring name;

    float cast_score;

    // construct and destruct
    patterns_params() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(patterns_params);

    // reflection
    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        CALLISTO_REFLECT(reflection, name);

        CALLISTO_REFLECT(reflection, cast_score);
    };
};

struct additional_params
{
    // data ---------------------------------------------------------------------------------------
    std::vector<int> indexes;

    std::vector<std::wstring> video_types;

    // construct and destruct ---------------------------------------------------------------------
    additional_params() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(additional_params);

    // reflection ---------------------------------------------------------------------------------
    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        CALLISTO_REFLECT(reflection, indexes);

        CALLISTO_REFLECT(reflection, video_types);
    }
};

template<typename stream_type>
stream_type& operator<<(stream_type& stream, const point3d& point)
{
    stream << "(" << point.x << ", " << point.y << ")";

    return stream;
}

struct polygon_data
{
    // data
    std::vector<std::array<int, 3>> polygon_order_array;

    std::vector<std::vector<int>> polygon_order_vector;

    std::vector<std::array<point3d, 3>> polygon_points;

    // construct and lifetime
    polygon_data() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(polygon_data);

    template<typename reflection_type>
    void self_reflect(reflection_type& reflection)
    {
        CALLISTO_REFLECT(reflection, polygon_order_array);

        CALLISTO_REFLECT(reflection, polygon_order_vector);

        CALLISTO_REFLECT_TAGS(
            reflection,
            polygon_points,
            c_f::streaming_reflector::tag::exist_stream_operator {}
        );
    }
};

struct math_settings
{
    // data
    point3d major_point;

    std::vector<point3d> auxiliary_points;

    std::array<point3d, 2> two_points;

    std::array<int, 4> four_values;

    polygon_data polygon;

    // construct and lifetime
    math_settings() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(math_settings);

    // reflection
    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        CALLISTO_REFLECT_TAGS(
            reflection,
            major_point,
            c_f::streaming_reflector::tag::exist_stream_operator {}
        );

        CALLISTO_REFLECT_TAGS(
            reflection,
            auxiliary_points,
            c_f::streaming_reflector::tag::exist_stream_operator {}
        );

        CALLISTO_REFLECT(reflection, two_points);

        CALLISTO_REFLECT(reflection, four_values);

        CALLISTO_REFLECT(reflection, polygon);
    }
};

struct foo_settings
{
    // data
    std::wstring foo;

    bool status1;

    bool status2;

    int age_value;

    std::wstring name;

    float skills;

    std::optional<additional_params> additional_data;

    additional_params additional_data1;

    std::shared_ptr<additional_params> additional_data2;

    std::unique_ptr<additional_params> additional_data3;

    patterns_params major_pattern;

    std::optional<patterns_params> minor_pattern;

    std::optional<patterns_params> free_pattern;

    std::vector<patterns_params> auxiliary_patterns;

    math_settings math;

    // construct and destruct
    foo_settings() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(foo_settings);

    // reflection
    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        CALLISTO_REFLECT_TAGS(
            reflection,
            foo,
            c_f::streaming_reflector::tag::exist_stream_operator {}
        );

        CALLISTO_REFLECT(reflection, status1);

        CALLISTO_REFLECT(reflection, status2);

        CALLISTO_REFLECT(reflection, age_value);

        CALLISTO_REFLECT(reflection, name);

        CALLISTO_REFLECT(reflection, skills);

        CALLISTO_REFLECT(reflection, additional_data);

        CALLISTO_REFLECT(reflection, additional_data1);

        CALLISTO_REFLECT(reflection, additional_data2);

        CALLISTO_REFLECT(reflection, additional_data3);

        CALLISTO_REFLECT(reflection, major_pattern);

        CALLISTO_REFLECT(reflection, minor_pattern);

        CALLISTO_REFLECT(reflection, free_pattern);

        CALLISTO_REFLECT(reflection, auxiliary_patterns);

        CALLISTO_REFLECT(reflection, math);
    }
};

namespace c_f = callisto::framework;

void example_json_serialization()

{
    std::wcout << std::boolalpha;
    namespace c_f = callisto::framework;

    auto reader = c_f::json_reading_reflector::read_from_file(L"resources/foo_bar.json");

    foo_settings settings;

    reader.read_to(settings);

    auto printer = c_f::streaming_reflector(
        std::wcout,
        0,
        c_f::streaming_reflector::str_quotes_type::single
    );
    printer.print(settings);

    std::cout
        << "---------------------------------------------------------------------------------";
    std::wstringstream wss;
    auto               second_printer
        = c_f::streaming_reflector(wss, 0, c_f::streaming_reflector::str_quotes_type::none);
    second_printer.print(settings);

    std::cout << "\nwstringstream:\n";
    std::wcout << wss.str() << "\n";

    std::cout << "a\tb\tc\t";
}

int main()
{
    try
    {
        example_json_serialization();
    }
    catch (const boost::exception& e)
    {
        std::cerr << "boost exception:" << boost::diagnostic_information(e) << "\n";

        const auto* wstring_err_msg = boost::get_error_info<c_f::error_tag_message_w>(e);
        if (wstring_err_msg != nullptr)
        {
            std::wcout << "wstring error message:" << *wstring_err_msg << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "default std exception:" << e.what() << '\n';
    }

    return 0;
}