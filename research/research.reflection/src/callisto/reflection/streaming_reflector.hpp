#pragma once

// std
#include <iostream>
#include <string>
#include <utility>
// project
#include <callisto/framework/concepts/core.hpp>
#include <string_auxiliary_can.hpp>

namespace callisto::framework
{

template<typename type>
struct custom_streaming_reflection
{
    static constexpr bool exist = false;

    static constexpr bool new_line = false;

    type& data;

    explicit custom_streaming_reflection(type& data) : data(data) {}

    template<typename stream_type>
    void stream_to(stream_type& stream)
    {
        static_assert("Not implement custom streaming for current type");
    }
};

// REMARK: очень тяжело писать всю эту залупу. Нужно поменять на вычислительный граф с памятью
//         и состояниями

namespace
{
template<typename type>
constexpr bool __is_can_nullable_v
    = is_std_optional_v<type> | is_std_shared_ptr_v<type> | is_std_unique_ptr_v<type>;
}

class streaming_reflector
{
public:
    struct tag
    {
        struct exist_stream_operator
        {
        };
    };

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

    str_quotes_type __quotes_type;

    // private methods
    void __print_tabs()
    {
        for (int32_t i = 0; i < __tab_count; i++)
        {
            __stream << "\t";
        }
    }

    enum class token_type
    {
        open_class,
        close_class,
        name,
        value,
        string,
        open_sequence,
        close_sequence
    };

    token_type __prev_token;

    void __stream_name(const wchar_t* name) {}

    void __print_concrete_str_type(std::string& str) { __stream << str2wide(str); }

    void __print_concrete_str_type(std::wstring& str) { __stream << str; }

    template<typename char_type>
    void __print_stream_operator_type(std::basic_string<char_type>& str)
    {
        auto quote_symbol = str_quotes_type_symbol(__quotes_type);

        if (quote_symbol != 0) __stream << quote_symbol;
        __print_concrete_str_type(str);
        if (quote_symbol != 0) __stream << quote_symbol;
    }

    template<typename type, typename... pack_type>
    void __print_stream_operator_type(type& ob)
    {
        if constexpr (is_custom_reflection_v<type>)
        {
            __stream << ob.data;
        }
        else
        {
            __stream << ob;
        }
    }

    template<typename tag_type>
    void __has_tag_exist_stream_operator(tag_type& tag, bool& exist_status)
    {
        if constexpr (std::is_same_v<tag_type, tag::exist_stream_operator>)
        {
            exist_status = true;
        }
    }

    template<typename type, typename tag_type>
    void __print_class_type_and_process_tag(type& ob, tag_type& tag, bool& already_stream)
    {
        if (already_stream) return;
        if constexpr (std::is_same_v<tag_type, tag::exist_stream_operator>)
        {
            __print_stream_operator_type(ob);
            __stream << "\n";
            already_stream = true;
        }
    }

    template<typename type, typename... pack_type>
    void __print_class_type(type& ob, pack_type&... tags)
    {
        bool already_stream = false;
        (__print_class_type_and_process_tag(ob, tags, already_stream), ...);

        if (already_stream) return;

        if constexpr (custom_streaming_reflection<type>::exist)
        {
            auto stream_handler = custom_streaming_reflection<type>(ob);
            stream_handler.stream_to(__stream);
        }
        else
        {
            if constexpr (custom_reflection<type>::exist)
            {
                auto custom_reflect_handler = custom_reflection<type>(ob);
                custom_reflect_handler.self_reflect(*this);
            }
            else
            {
                ob.self_reflect(*this);
            }
        }
    }

    template<typename type, typename... pack_type>
    void __print_primitive_span(std::span<type> span, bool after_name, pack_type&... tags)
    {
        __print_tabs();
        __stream << "[\n";
        for (size_t i = 0; i < span.size(); i++)
        {
            auto& val = span[i];
            __print_tabs();
            __stream << "\t";
            __print_stream_operator_type(val);
            __stream << "\n";
        }
        __print_tabs();
        __stream << "]\n";
    }

    template<typename type, typename... pack_type>
    void __print_class_span(std::span<type> span, bool after_name, pack_type&... tags)
    {
        __print_tabs();
        __stream << "[\n";
        for (size_t i = 0; i < span.size(); i++)
        {
            auto& val = span[i];

            if constexpr (is_std_vector_v<type> || is_std_array_v<type>)
            {
                __tab_count++;
            }

            bool exist_stream_operator_tag = false;
            (__has_tag_exist_stream_operator(tags, exist_stream_operator_tag), ...);
            if (exist_stream_operator_tag)
            {
                __print_tabs();
                __stream << "\t";
            }

            __reflect(val, nullptr, tags...);

            if constexpr (is_std_vector_v<type> || is_std_array_v<type>)
            {
                __tab_count--;
            }
            if (i != span.size() - 1) __stream << "\n";
        }
        __print_tabs();
        __stream << "]\n";
    }

    template<typename other_type, typename... pack_type>
    void
    __print_unique_ptr(std::unique_ptr<other_type>& ptr, const wchar_t* name, pack_type&... tags)
    {
        if (ptr == nullptr)
        {
            __stream << "none\n";
        }
        else
        {
            if (name != nullptr) __stream << "\n";
            __reflect(*ptr, nullptr, tags...);
        }
    }

    template<typename other_type, typename... pack_type>
    void
    __print_shared_ptr(std::shared_ptr<other_type>& ptr, const wchar_t* name, pack_type&... tags)
    {
        if (ptr == nullptr)
        {
            __stream << "none\n";
        }
        else
        {
            if (name != nullptr) __stream << "\n";
            __reflect(*ptr, nullptr, tags...);
        }
    }

    template<typename type, typename... pack_type>
    void __print_optional(std::optional<type>& opt_val, const wchar_t* name, pack_type&... tags)
    {
        if (!opt_val.has_value())
        {
            __stream << "none\n";
        }
        else
        {
            if (name != nullptr) __stream << "\n";
            auto& val = opt_val.value();
            __reflect(val, nullptr, tags...);
        }
    }

    template<typename type, typename... pack_type>
    void __print_span(std::span<type> span, pack_type&... tags)
    {

        if constexpr (std::is_same_v<type, std::string> || std::is_same_v<type, std::wstring> || std::is_arithmetic_v<type>)
        {
            __print_primitive_span(span, tags...);
        }
        else
        {
            __print_class_span(span, tags...);
        }
    }

    template<typename type, typename... pack_type>
    void __print_vector(std::vector<type>& vec, const wchar_t* name, pack_type&... tags)
    {
        auto span_handler = std::span<type>(vec);
        __print_span(span_handler, name, tags...);
    }

    template<typename type, size_t n, typename... pack_type>
    void __print_array(std::array<type, n>& arr, const wchar_t* name, pack_type&... tags)
    {
        auto span_handler = std::span<type>(arr);
        __print_span(span_handler, name, tags...);
    }

    // default implementation
    template<typename type, typename... pack_type>
    void __reflect(type& val, const wchar_t* name = nullptr, pack_type&&... tags)
    {
        bool tab_increment_flag = false;

        if (name != nullptr)
        {
            __print_tabs();
            __stream << name << ": ";
        }

        if constexpr (__is_can_nullable_v<type>)
        {
            if constexpr (is_std_optional_v<type>)
            {
                __print_optional(val, name, tags...);
            }
            else if constexpr (is_std_unique_ptr_v<type>)
            {
                __print_unique_ptr(val, name, tags...);
            }
            else if constexpr (is_std_shared_ptr_v<type>)
            {
                __print_shared_ptr(val, name, tags...);
            }
        }
        else
        {
            if constexpr (is_std_sequential_container_v<type>)
            {
                if (name != nullptr) __stream << "\n";
                /*
                if (name != nullptr)
                {
                    __print_tabs();
                    __stream << name << ":\n";
                }
                */
                if constexpr (is_std_vector_v<type>)
                {
                    __print_vector(val, name, tags...);
                }
                else if constexpr (is_std_array_v<type>)
                {
                    __print_array(val, name, tags...);
                }
            }
            else
            {
                /*
                if (name != nullptr)
                {
                    __print_tabs();
                    __stream << name << ": ";
                }
                */

                __tab_count++;
                tab_increment_flag = true;

                if constexpr (std::is_arithmetic_v<type>)
                {
                    __print_stream_operator_type(val);
                    __stream << "\n";
                }
                else if constexpr (is_std_basic_string_v<type>)
                {
                    __print_stream_operator_type(val);
                    __stream << "\n";
                }
                else
                {
                    bool exist_stream_operator_tag = false;
                    (__has_tag_exist_stream_operator(tags, exist_stream_operator_tag), ...);

                    if (name != nullptr && !exist_stream_operator_tag)
                    {
                        __stream << "\n";
                    }
                    __print_class_type(val, tags...);
                }
            }
        }

        if (tab_increment_flag)
        {
            __tab_count--;
        }
    }

public:
    // construct and destruct
    streaming_reflector(
        std::wostream&  stream,
        int32_t         tab_count   = 0,
        str_quotes_type quotes_type = str_quotes_type::single
    ) :
        __stream(stream), __tab_count(tab_count), __quotes_type(quotes_type)
    {
    }

    // methods
    template<typename type>
    void print(type& ob)
    {
        ob.self_reflect(*this);
    }

    // default implementation
    template<typename type, typename... pack_type>
    void reflect(type& val, const wchar_t* name = nullptr, pack_type&&... tags)
    {
        __reflect(val, name, tags...);
    }
};

} // namespace callisto::framework