#pragma once

// std
#include <vector>
#include <string>

namespace placeholder
{

struct parameter_tag
{
    struct floating_param
    {
        double min;

        double max;

        double step;
    };

    struct integer_param
    {
        int min;

        int max;

        int step;
    };

    struct str_list
    {
        using string_list_type = std::vector<std::pair<std::wstring_view, std::wstring_view>>;
        const std::vector<std::wstring_view>& data;

        constexpr explicit str_list(const std::vector<std::wstring_view>& data) : data(data) {}
    };

    struct str_code_list
    {
        using string_list_type = std::vector<std::pair<std::wstring_view, std::wstring_view>>;

        const string_list_type& data;

        constexpr explicit str_code_list(const string_list_type& data) : data(data) {}
    };

    struct enum_str_code_list
    {
        using enum_string_list_type = std::vector<std::pair<int32_t, std::wstring_view>>;

        const enum_string_list_type& data;

        constexpr explicit enum_str_code_list(const enum_string_list_type& data) : data(data) {}
    };

    struct bool_str_list
    {
        std::wstring_view true_present;

        std::wstring_view false_present;

        constexpr explicit bool_str_list(
            std::wstring_view true_present,
            std::wstring_view false_present
        ) :
            true_present(true_present), false_present(false_present)
        {
        }
    };

    struct mutable_list
    {
    };
};

class placeholder_ui_setter

{

private:
    template<typename... tag_pack_type>
    void __reflect_bool(bool& val, const wchar_t* name, tag_pack_type&... tags)
    {
    }

    template<typename float_type, typename... tag_pack_type>
    void __reflect_floating(float_type& val, const wchar_t* name, tag_pack_type&... tags)
    {
    }

public:
};

} // namespace placeholder