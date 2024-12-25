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

#include <callisto/framework/types/type_traits/std_classes.hpp>
#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/exception.hpp>

#include "callisto_reflection.hpp"
#include <string_auxiliary_can.hpp>

namespace callisto::framework
{

class json_reader_element
{
public:
    friend class json_reading_reflector;

private:
    // data
    boost::property_tree::wptree& __tree;

    const wchar_t* __name;

    // construct and destruct
    explicit json_reader_element(boost::property_tree::wptree& tree, const wchar_t* name = L"") :
        __tree(tree), __name(name)
    {
    }

#pragma region private_methods

    template<typename type, typename... pack_type>
    void __read_class_type(type& val, pack_type&... tags)
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

    template<typename... pack_type>
    void __read_str(std::string& val, pack_type&... tags)
    {
        val = callisto::framework::cut_wide2str(__tree.get_value<std::wstring>());
    };

    template<typename... pack_type>
    void __read_str(std::wstring& val, pack_type&... tags)
    {
        val = __tree.get_value<std::wstring>();
    }

    template<callisto::framework::concept_arithmetic arithmetic_type, typename... pack_type>
    void __read_arithmetic(arithmetic_type& val, pack_type&... tags)
    {
        val = __tree.get_value<arithmetic_type>();
    }

    template<typename... pack_type>
    void __read_bool(bool& val, pack_type&... tags)
    {
        auto str_val = __tree.get_value<std::wstring>();
        if (str_val == L"true")
        {
            val = true;
        }
        else
        {
            val = false;
        }
    }

    template<typename type, typename... pack_type>
    void __read_unique_ptr(std::unique_ptr<type>& ptr, pack_type&... tags)
    {
        if (ptr == nullptr)
        {
            ptr = std::make_unique<type>();
        }
        reflect(*ptr, nullptr, tags...);
    }

    template<typename type, typename... pack_type>
    void __read_shared_ptr(std::shared_ptr<type>& ptr, pack_type&... tags)
    {
        if (ptr == nullptr)
        {
            ptr = std::make_shared<type>();
        }
        reflect(*ptr, nullptr, tags...);
    }

    template<typename type, typename... pack_type>
    void __read_optional(std::optional<type>& opt_val, pack_type&... tags)
    {
        auto preval = __tree.get_value<std::wstring>();
        if (preval == L"null")
        {
            opt_val = std::nullopt;
        }
        else
        {
            type t;
            reflect(t, nullptr, tags...);
            opt_val = std::move(t);
        }
    }

    template<typename type, typename... pack_type>
    void __read_span(std::span<type> span, pack_type&... tags)
    {
        size_t idx = 0;
        for (auto& child : __tree)
        {
            type ob;
            auto new_element = json_reader_element(child.second);

            new_element.reflect(ob, nullptr, tags...);
            span[idx] = std::move(ob);
            idx++;
        }
    }

    template<typename type, typename... pack_type>
    void __read_vector(std::vector<type>& vec, pack_type&... tags)
    {
        vec.resize(__tree.size());
        auto span_handler = std::span<type>(vec);

        __read_span(span_handler, tags...);
    }

    template<typename type, size_t n, typename... pack_type>
    void __read_array(std::array<type, n>& arr, pack_type&... tags)
    {
        if (__tree.size() != n)
        {
            // FUTURE add print path
            CALLISTO_THROW_EXCEPTION(runtime_exception()) << error_tag_message_w(_wbs(
                "std::array size != array size in json,"
                " name: ",
                __name,
                ". ",
                n,
                " != ",
                __tree.size(),
                "."
            ));
        }
        auto span_handler = std::span<type>(arr);

        __read_span(span_handler, tags...);
    }

#pragma endregion

public:
    // lifetime
    CALLISTO_LIFETIME_REFERENCE(json_reader_element);

#pragma region methods

    template<typename type, typename... pack_type>
    void reflect(type& val, const wchar_t* name, pack_type&&... tags)
    {
        if (name != nullptr)
        {
            auto& child_tree = __tree.get_child(name);

            auto new_element = json_reader_element(child_tree, name);

            new_element.reflect(val, nullptr, tags...);
        }
        else
        {
            if constexpr (is_std_vector_v<type>)
            {
                __read_vector(val, tags...);
            }
            else if constexpr (is_std_array_v<type>)
            {
                __read_array(val, tags...);
            }
            else if constexpr (is_std_optional_v<type>)
            {
                __read_optional(val, tags...);
            }
            else if constexpr (is_std_unique_ptr_v<type>)
            {
                __read_unique_ptr(val, tags...);
            }
            else if constexpr (is_std_shared_ptr_v<type>)
            {
                __read_shared_ptr(val, tags...);
            }
            else if constexpr (std::is_same_v<type, bool>)
            {
                __read_bool(val, tags...);
            }
            else if constexpr (std::is_arithmetic_v<type>)
            {
                __read_arithmetic(val, tags...);
            }
            else if constexpr (is_std_basic_string_v<type>)
            {
                __read_str(val, tags...);
            }
            else
            {
                __read_class_type(val, tags...);
            }
        }
    }

    template<typename type>
    void read(type& ob)
    {
        ob.self_reflect(*this);
    }

#pragma endregion
};

class json_reading_reflector
{
    boost::property_tree::wptree __root;

    std::unique_ptr<json_reader_element> __element;

    void __initialize_data(std::wstringstream& wss)
    {
        boost::property_tree::read_json(wss, __root);
        __element.reset(new json_reader_element(__root));
    }

public:
    CALLISTO_LIFETIME_REFERENCE(json_reading_reflector);

    explicit json_reading_reflector(const std::wstring& json_str)
    {
        std::wstringstream wss;
        wss << json_str;

        __initialize_data(wss);
    }

    explicit json_reading_reflector(std::wstringstream& wss) { __initialize_data(wss); }

    static json_reading_reflector read_from_file(const wchar_t* path)
    {
        auto file = std::wfstream(path);
        file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();

        return json_reading_reflector(wss);
    }

    static json_reading_reflector read_from_file(const char* path)
    {
        auto file = std::wfstream(path);
        file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();

        return json_reading_reflector(wss);
    }

    template<typename type>
    void read_to(type& val)
    {
        val.self_reflect(*__element);
    }
};

} // namespace callisto::framework