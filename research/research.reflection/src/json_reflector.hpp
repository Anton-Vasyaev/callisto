#pragma once

// std
#include <memory>
#include <string>
#include <optional>
#include <span>
#include <vector>
// 3rd party
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/exception.hpp>

#include <string_auxiliary_can.hpp>

namespace callisto::framework
{

class json_reader_element
{
public:
    friend class json_reading_reflection;

private:
    // data
    boost::property_tree::wptree& __tree;

    explicit json_reader_element(boost::property_tree::wptree& tree) : __tree(tree) {}

public:
    CALLISTO_LIFETIME_REFERENCE(json_reader_element);

    template<typename type>
    void reflect_class_type(type& val)
    {
        if constexpr (custom_reflection<type>::exist)
        {
            auto custom_reflect_handler = custom_reflection<type>(val);
            custom_reflect_handler.self_reflect(*this);
        }
        else
        {
            val.self_reflect(*this);
        }
    }

    // default methods
    template<typename type>
    void reflect(type& val, const wchar_t* name)
    {
        auto& child_tree = __tree.get_child(name);

        auto new_element = json_reader_element(child_tree);

        new_element.reflect_class_type(val);
    }

    template<>
    void reflect(std::string& val, const wchar_t* name)
    {
        val = callisto::framework::cut_wide2str(__tree.get<std::wstring>(name));
    };

    template<>
    void reflect(std::wstring& val, const wchar_t* name)
    {
        val = __tree.get<std::wstring>(name);
    }

    template<callisto::framework::concept_arithmetic arithmetic_type>
    void reflect(arithmetic_type& val, const wchar_t* name)
    {
        val = __tree.get<arithmetic_type>(name);
    }

    template<>
    void reflect(bool& val, const wchar_t* name)
    {
        auto str_val = __tree.get<std::wstring>(name);
        if (str_val == L"true")
        {
            val = true;
        }
        else
        {
            val = false;
        }
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

    template<typename type>
    void reflect(std::shared_ptr<type>& ptr, const wchar_t* name)
    {
        if (ptr == nullptr)
        {
            ptr = std::make_shared<type>();
        }
        reflect(*ptr, name);
    }

    template<typename type>
    void reflect(std::optional<type>& opt_val, const wchar_t* name)
    {
        auto preval = __tree.get<std::wstring>(name);
        if (preval == L"null")
        {
            opt_val = std::nullopt;
        }
        else
        {
            type t;
            reflect(t, name);
            opt_val = std::move(t);
        }
    }

    template<callisto::framework::concept_arithmetic arithmetic_type>
    void reflect_arithmetic_span(std::span<arithmetic_type> span, const wchar_t* name)
    {
        size_t idx = 0;
        for (auto& child : __tree.get_child(name))
        {
            auto val  = child.second.get_value<arithmetic_type>();
            span[idx] = val;
            idx++;
        }
    }

    // template<>
    void reflect_str_span(std::span<std::string> span, const wchar_t* name)
    {
        CALLISTO_THROW_EXCEPTION(callisto::framework::not_implemented_exception());
    }

    // template<>
    void reflect_wstr_span(std::span<std::wstring> span, const wchar_t* name)
    {
        size_t idx = 0;
        for (auto& child : __tree.get_child(name))
        {
            auto str_val = child.second.get_value<std::wstring>();
            span[idx]    = std::move(str_val);
            idx++;
        }
    }

    template<typename type>
    void reflect_span(std::span<type> span, const wchar_t* name)
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
            size_t idx = 0;
            for (auto& child : __tree.get_child(name))
            {
                type ob;
                auto new_element = json_reader_element(child.second);

                new_element.reflect_class_type(ob);
                span[idx] = std::move(ob);
                idx++;
            }
        }
    }

    template<typename type>
    void reflect(std::vector<type>& vec, const wchar_t* name)
    {
        auto arr_child = __tree.get_child(name);
        vec.resize(arr_child.size());
        auto span_handler = std::span<type>(vec);

        reflect_span(span_handler, name);
    }

    template<typename type, size_t n>
    void reflect(std::array<type, n>& arr, const wchar_t* name)
    {
        auto arr_child = __tree.get_child(name);
        if (arr_child.size() != n)
        {
            // FUTURE add print path
            CALLISTO_THROW_EXCEPTION(runtime_exception()) << error_tag_message_w(_wbs(
                "std::array size != array size in json,"
                " name: ",
                name,
                ". ",
                n,
                " != ",
                arr_child.size(),
                "."
            ));
        }
        auto span_handler = std::span<type>(arr);

        reflect_span(span_handler, name);
    }

    // methods
    template<typename type>
    void read(type& ob)
    {
        ob.self_reflect(*this);
    }
};

class json_reading_reflection
{
    boost::property_tree::wptree __root;

    std::unique_ptr<json_reader_element> __element;

    void __initialize_data(std::wstringstream& wss)
    {
        boost::property_tree::read_json(wss, __root);
        __element.reset(new json_reader_element(__root));
    }

public:
    CALLISTO_LIFETIME_REFERENCE(json_reading_reflection);

    explicit json_reading_reflection(const std::wstring& json_str)
    {
        std::wstringstream wss;
        wss << json_str;

        __initialize_data(wss);
    }

    explicit json_reading_reflection(std::wstringstream& wss) { __initialize_data(wss); }

    static json_reading_reflection read_from_file(const wchar_t* path)
    {
        auto file = std::wfstream(path);
        file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();

        return json_reading_reflection(wss);
    }

    static json_reading_reflection read_from_file(const char* path)
    {
        auto file = std::wfstream(path);
        file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();

        return json_reading_reflection(wss);
    }

    template<typename type>
    void read_to(type& val)
    {
        val.self_reflect(*__element);
    }
};

} // namespace callisto::framework