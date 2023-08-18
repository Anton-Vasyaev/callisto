#ifndef CALLISTO_FRAMEWORK_DEFAULT_DISPOSER_HPP
#define CALLISTO_FRAMEWORK_DEFAULT_DISPOSER_HPP

namespace callisto::framework
{
    template<typename data_type>
    struct default_disposer
    {
        void operator()(data_type data);
    };
}

#endif