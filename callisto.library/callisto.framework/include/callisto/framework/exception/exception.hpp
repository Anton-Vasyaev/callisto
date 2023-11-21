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
    static constexpr const char* default_message = "default error message (not exist).";

    mutable std::string _formed_error_message;

public:
    virtual std::string form_error_message() const { return exception::default_message; }

    virtual const char* what() const noexcept
    {
        try
        {
            if (_formed_error_message.empty())
            {
                _formed_error_message = std::move(form_error_message());
            }
        }
        catch(...)
        {
            return exception::default_message;
        }

        return _formed_error_message.c_str();
    }
};

} // namespace callisto::framework