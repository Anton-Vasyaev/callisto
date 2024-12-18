// std
#include <iostream>
#include <memory>
#include <codecvt>
// 3rd party
#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/concepts/core.hpp>

#include "callisto_reflect.hpp"
#include "json_reflector.hpp"

#include "string_auxiliary_can.hpp"

class placeholder_reflect_writer
{
public:
    template<typename type>
    void reflect(type& val, const wchar_t* name)
    {
        val.self_reflect(*this);
    }

    template<>
    void reflect(std::string& val, const wchar_t* name)
    {
        val = std::string("value") + "c_str_placeholder_name";
    };

    template<>
    void reflect(std::wstring& val, const wchar_t* name)
    {
        val = std::wstring(L"value:") + name;
    }

    template<callisto::framework::concept_integer int_type>
    void reflect(int_type& val, const wchar_t* name)
    {
        val = 1024;
    }

    template<callisto::framework::concept_floating_point float_type>
    void reflect(float_type& val, const wchar_t* name)
    {
        val = 3.14;
    }

    template<>
    void reflect(bool& val, const wchar_t* name)
    {
        val = true;
    }

    template<typename type>
    void reflect(std::unique_ptr<type>& ptr, const wchar_t* name)
    {
        if (ptr == nullptr)
        {
            ptr = std::make_unique<type>();
        }
        reflect(*ptr, name);
    }
};

class reflection_streamer
{
public:
    enum class str_quotes_type
    {
        none,
        single,
        double_
    };

private:
    static constexpr char str_quotes_type_symbol(str_quotes_type type)
    {
        switch (type)
        {
            case str_quotes_type::single : return 39;
            case str_quotes_type::double_ : return '"';
            default : return 0;
        }
    }

    std::wostream& __stream;

    int32_t __tab_count;

    bool __stream_names;

    str_quotes_type __quotes_type;

    const char* __sequence_separation_str;

    bool __sequence_element_new_line;

    bool __sequence_braces;

    // private methods
    void __print_tabs()
    {
        for (int32_t i = 0; i < __tab_count; i++)
        {
            __stream << "\t";
        }
    }

    void __print_str(std::string& str) { __stream << callisto::framework::str2wide(str); }

    void __print_str(std::wstring& str) { __stream << str; }

    template<typename char_type>
    void __print_type(std::basic_string<char_type>& str)
    {
        auto quote_symbol = str_quotes_type_symbol(__quotes_type);

        if (quote_symbol != 0) __stream << quote_symbol;
        __print_str(str);
        if (quote_symbol != 0) __stream << quote_symbol;
    }

    template<typename type>
    void __print_type(type& ob)
    {
        __stream << ob;
    }

    template<typename type>
    void __print_primitive_span(std::span<type> span)
    {
        if (__sequence_braces) __stream << "[";

        for (size_t i = 0; i < span.size(); i++)
        {
            if (__sequence_element_new_line)
            {
                __stream << "\n\t";
                __print_tabs();
            }

            auto& val = span[i];
            __print_type(val);

            if (i != span.size() - 1) __stream << __sequence_separation_str;
        }

        if (__sequence_braces)
        {
            if (__sequence_element_new_line)
            {
                __stream << "\n";
                __print_tabs();
            }

            __stream << "]";
        }

        __stream << "\n";
    }

    template<typename type>
    void __print_class_span(std::span<type> span)
    {
        if (__sequence_braces) __stream << "[";

        for (size_t i = 0; i < span.size(); i++)
        {
            __stream << "\n";
            auto& val    = span[i];
            auto  new_el = reflection_streamer(
                __stream,
                __tab_count + 1,
                __stream_names,
                __quotes_type,
                __sequence_separation_str,
                __sequence_element_new_line,
                __sequence_braces
            );
            new_el.print(val);
        }

        if (__sequence_braces)
        {
            if (__sequence_element_new_line)
            {
                __stream << "\n";
                __print_tabs();
            }

            __stream << "]";
        }

        __stream << "\n";
    }

public:
    // construct and destruct
    reflection_streamer(
        std::wostream&  stream,
        int32_t         tab_count                 = 0,
        bool            stream_names              = true,
        str_quotes_type quotes_type               = str_quotes_type::single,
        const char*     sequence_separation_str   = " ",
        bool            sequence_element_new_line = false,
        bool            sequence_braces           = true
    ) :
        __stream(stream)
    {
        __tab_count = tab_count;

        __stream_names = stream_names;

        __quotes_type = quotes_type;

        __sequence_separation_str = sequence_separation_str;

        __sequence_element_new_line = sequence_element_new_line;

        __sequence_braces = sequence_braces;
    }

    // methods
    template<typename type>
    void print(type& ob)
    {
        if constexpr (callisto::framework::custom_reflection<type>::exist)
        {
            auto reflection_handler = callisto::framework::custom_reflection<type>(ob);
            reflection_handler.self_reflect(*this);
        }
        else
        {
            ob.self_reflect(*this);
        }
    }

    // default implementation
    template<typename type>
    void reflect(type& val, const wchar_t* name)
    {
        if (__stream_names)
        {
            __print_tabs();
            __stream << name << ":\n";
        }
        auto new_el = reflection_streamer(
            __stream,
            __tab_count + 1,
            __stream_names,
            __quotes_type,
            __sequence_separation_str,
            __sequence_element_new_line,
            __sequence_braces
        );
        new_el.print(val);
    }

    template<>
    void reflect(std::string& val, const wchar_t* name)
    {
        namespace c_f = callisto::framework;

        __print_tabs();

        if (__stream_names) __stream << name << ": ";
        __stream << c_f::str2wide(val) << "\n";
    };

    template<>
    void reflect(std::wstring& val, const wchar_t* name)
    {
        __print_tabs();
        if (__stream_names) __stream << name << ": ";
        __stream << val << "\n";
    }

    template<callisto::framework::concept_arithmetic arithmetic_type>
    void reflect(arithmetic_type& val, const wchar_t* name)
    {
        __print_tabs();
        if (__stream_names) __stream << name << ": ";
        __stream << val << "\n";
    }

    template<typename other_type>
    void reflect(std::unique_ptr<other_type>& ptr, const wchar_t* name)
    {
        if (ptr == nullptr)
        {
            return;
        }
        reflect(*ptr, name);
    }

    template<typename other_type>
    void reflect(std::shared_ptr<other_type>& ptr, const wchar_t* name)
    {
        if (ptr == nullptr)
        {
            return;
        }
        reflect(*ptr, name);
    }

    template<typename type>
    void reflect(std::optional<type>& opt_val, const wchar_t* name)
    {
        if (!opt_val.has_value())
        {
            __print_tabs();
            if (__stream_names) __stream << name << ": ";
            __stream << "none\n";
        }
        else
        {
            auto& val = opt_val.value();
            reflect(val, name);
        }
    }

    template<callisto::framework::concept_arithmetic arithmetic_type>
    void reflect_arithmetic_span(std::span<arithmetic_type> span, const wchar_t* name)
    {
        __print_tabs();
        if (__stream_names) __stream << name << ": ";
        __print_primitive_span(span);
    }

    void reflect_str_span(std::span<std::string> span, const wchar_t* name)
    {
        __print_tabs();
        if (__stream_names) __stream << name << ": ";
        __print_primitive_span(span);
    }

    void reflect_wstr_span(std::span<std::wstring> span, const wchar_t* name)
    {
        __print_tabs();
        if (__stream_names) __stream << name << ": ";
        __print_primitive_span(span);
    }

    template<typename type>
    void reflect_class_span(std::span<type> span, const wchar_t* name)
    {
        __print_tabs();
        if (__stream_names) __stream << name << ": ";
        __print_class_span(span);
    }

    template<typename type>
    void reflect(std::span<type> span, const wchar_t* name)
    {
        if constexpr (std::is_same_v<type, std::string>)
        {
            reflect_str_span(span, name);
        }
        else if constexpr (std::is_same_v<type, std::wstring>)
        {
            reflect_wstr_span(span, name);
        }
        else if constexpr (std::is_arithmetic_v<type>)
        {
            reflect_arithmetic_span(span, name);
        }
        else
        {
            reflect_class_span(span, name);
        }
    }

    template<typename type>
    void reflect(std::vector<type>& vec, const wchar_t* name)
    {
        auto span_handler = std::span<type>(vec);
        reflect(span_handler, name);
    }

    template<typename type, size_t n>
    void reflect(std::array<type, n>& arr, const wchar_t* name)
    {
        auto span_handler = std::span<type>(arr);
        reflect(span_handler, name);
    }
};

struct custom_params_a
{
    std::wstring log_file;

    bool log_status;

    custom_params_a() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(custom_params_a);

    template<typename reflect_type>
    void self_reflect(reflect_type& reflect_ob)
    {
        CALLISTO_REFLECT(reflect_ob, log_file);
        CALLISTO_REFLECT(reflect_ob, log_status);
    }
};

struct custom_params_b
{
    // data ------------------------------------------------------------------------
    std::string str_name;

    std::wstring wstr_name;

    int32_t int_val;

    float float_val;

    std::unique_ptr<custom_params_a> params_a1;

    custom_params_a params_a2;

    std::shared_ptr<custom_params_a> params_a3;

    // construct and lifetime  -----------------------------------------------------
    custom_params_b() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(custom_params_b);

    // reflection  -----------------------------------------------------------------
    template<typename reflect_type>
    void self_reflect(reflect_type& reflect_ob)
    {
        CALLISTO_REFLECT(reflect_ob, str_name);

        CALLISTO_REFLECT(reflect_ob, wstr_name);
        CALLISTO_REFLECT(reflect_ob, int_val);
        CALLISTO_REFLECT(reflect_ob, float_val);
        CALLISTO_REFLECT(reflect_ob, params_a1);
        CALLISTO_REFLECT(reflect_ob, params_a2);
        CALLISTO_REFLECT(reflect_ob, params_a3);
    }
};

void example_ptree()
{
    namespace pt = boost::property_tree;

    pt::wptree root;

    auto file = std::wfstream(L"resources/foo_bar.json");
    file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << file.rdbuf();

    pt::read_json(wss, root);

    auto el = root.get_child(L"status1");

    auto val = el.get_value<std::wstring>();

    std::wcout << "val:" << val << "\n";

    auto b_val = el.get_value<bool>();
    std::wcout << "b val:" << b_val << "\n";

    auto el2    = root.get_child(L"status2");
    auto b_val2 = el2.get_value<bool>();

    std::wcout << "b val:" << b_val << "\n";

    auto aux_patt_el = root.get_child(L"auxiliary_patterns");
    std::cout << "size:" << aux_patt_el.size() << "\n";
    std::cout << "count:" << root.count(L"auxiliary_patterns") << "\n";

    // auto el = root.get_child_optional(L"not_exist_field");
}

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
    // data
    std::vector<int> indexes;

    std::vector<std::wstring> video_types;

    // construct and destruct
    additional_params() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(additional_params);

    // reflection
    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        CALLISTO_REFLECT(reflection, indexes);

        CALLISTO_REFLECT(reflection, video_types);
    }
};

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

    point3d& point;

    explicit custom_reflection(point3d& point) : point(point) {}

    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        reflection.reflect(point.x, L"x");
        reflection.reflect(point.y, L"y");
        reflection.reflect(point.z, L"z");
    }
};
} // namespace callisto::framework

struct math_settings
{
    point3d major_point;

    std::vector<point3d> auxiliary_points;

    std::array<point3d, 2> two_points;

    std::array<int, 4> four_values;

    math_settings() = default;

    CALLISTO_LIFETIME_MOVE_DEFAULT(math_settings);

    template<typename reflect_type>
    void self_reflect(reflect_type& reflection)
    {
        CALLISTO_REFLECT(reflection, major_point);

        CALLISTO_REFLECT(reflection, auxiliary_points);

        CALLISTO_REFLECT(reflection, two_points);

        CALLISTO_REFLECT(reflection, four_values);
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

        CALLISTO_REFLECT(reflection, foo);

        CALLISTO_REFLECT(reflection, status1);

        CALLISTO_REFLECT(reflection, status2);

        CALLISTO_REFLECT(reflection, age_value);

        CALLISTO_REFLECT(reflection, name);

        CALLISTO_REFLECT(reflection, skills);

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

void example_json_serialization()

{
    std::wcout << std::boolalpha;
    namespace c_f = callisto::framework;

    auto reader = c_f::json_reading_reflection::read_from_file(L"resources/foo_bar.json");

    foo_settings settings;

    reader.read_to(settings);

    std::wcout << settings.additional_data2->video_types[0] << "\n";

    auto printer = reflection_streamer(
        std::wcout,
        0,
        true,
        reflection_streamer::str_quotes_type::single,
        "; ",
        true,
        true
    );
    printer.print(settings);

    std::wstringstream wss;
    auto               second_printer = reflection_streamer(wss, 0, false);
    second_printer.print(settings);

    std::cout << "\nwstringstream:\n";
    std::wcout << wss.str() << "\n";

    std::cout << "a\tb\tc\t";
}

namespace c_f = callisto::framework;

int main()
{
    try
    {
        // example_placeholder();
        // example_ptree();
        example_json_serialization();

        // example_str_can();
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