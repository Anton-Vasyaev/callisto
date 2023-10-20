#pragma once

namespace callisto::framework
{
    template<typename data_type>
    struct default_disposer
    {
        void operator()(data_type data);
    };
}
