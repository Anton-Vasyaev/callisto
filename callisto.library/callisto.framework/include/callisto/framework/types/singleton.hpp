#pragma once

namespace callisto::framework
{

template<typename type>
class singleton
{

public:
    // lifetime
    singleton() = delete;

    singleton(const singleton&) = delete;

    singleton(singleton&&) = delete;

    singleton& operator=(const singleton&) = delete;

    singleton& operator=(singleton&&) = delete;

    // methods
    static type& get_instance()
    {
        static type instance;

        return instance;
    }
};

} // namespace callisto::framework