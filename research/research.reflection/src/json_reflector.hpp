#pragma once

// std
#include <memory>
#include <string>
#include <optional>

// 3rd party
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/exception.hpp>

#include <string_auxiliary_can.hpp>

#include <callisto/reflection/manual_parameter.hpp>

namespace callisto::framework
{

class json_reader_element
{
public:
    friend class json_reader;

private:
    // data
    boost::property_tree::wptree& __tree;

    explicit json_reader_element(boost::property_tree::wptree& tree) : __tree(tree) {}

public:
    CALLISTO_LIFETIME_REFERENCE(json_reader_element);

    // default methods
    template<typename type>
    void reflect(type& val, const wchar_t* name)
    {
        auto& child_tree = __tree.get_child(name);

        auto new_element = json_reader_element(child_tree);

        val.self_reflect(new_element);
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
    void reflect_arithmetic_vec(std::vector<arithmetic_type>& vec, const wchar_t* name)
    {
        for (auto& child : __tree.get_child(name))
        {
            auto val = child.second.get_value<arithmetic_type>();
            vec.push_back(val);
        }
    }

    // template<>
    void reflect_str_vec(std::vector<std::string>& vec, const wchar_t* name)
    {
        CALLISTO_THROW_EXCEPTION(callisto::framework::not_implemented_exception());
    }

    // template<>
    void reflect_wstr_vec(std::vector<std::wstring>& vec, const wchar_t* name)
    {
        for (auto& child : __tree.get_child(name))
        {
            auto str_val = child.second.get_value<std::wstring>();
            vec.push_back(std::move(str_val));
        }
    }

    template<typename type>
    void reflect(std::vector<type>& vec, const wchar_t* name)
    {
        if constexpr (std::is_same_v<type, std::string>)
        {
            reflect_str_vec(vec, name);
        }
        else if constexpr (std::is_same_v<type, std::wstring>)
        {
            reflect_wstr_vec(vec, name);
        }
        else if constexpr (std::is_arithmetic_v<type>)
        {
            reflect_arithmetic_vec(vec, name);
        }
        else
        {
            for (auto& child : __tree.get_child(name))
            {
                type ob;
                auto new_element = json_reader_element(child.second);

                ob.self_reflect(new_element);
                vec.push_back(std::move(ob));
            }
        }
    }

    // methods
    template<typename type>
    void read(type& ob)
    {
        ob.self_reflect(*this);
    }
};

class json_reader
{
    boost::property_tree::wptree __root;

    std::unique_ptr<json_reader_element> __element;

    void __initialize_data(std::wstringstream& wss)
    {
        boost::property_tree::read_json(wss, __root);
        __element.reset(new json_reader_element(__root));
    }

public:
    CALLISTO_LIFETIME_REFERENCE(json_reader);

    explicit json_reader(const std::wstring& json_str)
    {
        std::wstringstream wss;
        wss << json_str;

        __initialize_data(wss);
    }

    explicit json_reader(std::wstringstream& wss) { __initialize_data(wss); }

    static json_reader read_from_file(const wchar_t* path)
    {
        auto file = std::wfstream(path);
        file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();

        return json_reader(wss);
    }

    static json_reader read_from_file(const char* path)
    {
        auto file = std::wfstream(path);
        file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();

        return json_reader(wss);
    }

    template<typename type>
    void read_to(type& val)
    {
        val.self_reflect(*__element);
    }
};

} // namespace callisto::framework