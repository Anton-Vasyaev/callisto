#pragma once

// std
#include <exception>
// 3rd party
#include <boost/exception/all.hpp>

namespace callisto::framework
{

/// @brief Present base exception.
struct exception : virtual std::exception, virtual boost::exception
{
private:
    mutable std::string _formed_error_message;

public:
    virtual std::string form_error_message() const { return "default error message (not exist)."; }

    virtual const char* what() const
    {
        if (_formed_error_message.empty())
        {
            _formed_error_message = std::move(form_error_message());
        }

        return _formed_error_message.c_str();
    }
};

} // namespace callisto::framework