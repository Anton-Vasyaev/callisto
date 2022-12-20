#ifndef CALLISTO_FRAMEWORK_UNIQUE_SCOPE_HANDLER_HPP
#define CALLISTO_FRAMEWORK_UNIQUE_SCOPE_HANDLER_HPP

// std
#include <utility>
// project
#include "default_disposer.hpp"


namespace callisto::framework
{
    template<
        typename _data_type, 
        typename _disposer_type=default_disposer<_data_type>>
    class unique_handler
    {
    private:
        using data_type = _data_type;

        using disposer_type = _disposer_type;


        bool has_data = false;

        data_type data;

        disposer_type disposer;

        #pragma region private_methods

        inline void destroy()
        {
            if(this->has_data)
            {
                this->disposer(this->data);
                this->has_data = false;
            }
        }

        inline void move_from_other(
            unique_handler&& other_handler
        )
        {
            this->destroy();
            this->disposer = other_handler.disposer;
            this->data = other_handler.data;
            this->has_data = other_handler.has_data;
            other_handler.has_data = false;
        }

        #pragma endregion

    public:
        #pragma region construct_and_destruct

        unique_handler() { }

        ~unique_handler()
        {
            this->destroy();
        }

        unique_handler(
            data_type data
        ) 
        { 
            this->data = data;
            this->has_data = true;
        }

        unique_handler(
            const unique_handler&
        ) = delete;

        unique_handler(
            unique_handler&& other_handler
        )
        {
            this->move_from_other(std::move(other_handler));
        }

        #pragma endregion


        #pragma region methods

        void dispose() { this->destroy(); }

        void reset(data_type data)
        {
            this->destroy();
            this->data = data;
            this->hasData = true;
        }

        data_type release()
        {
            auto release_data = this->data;
            this->has_data = false;
            return release_data;
        }

        #pragma endregion


        #pragma region operators

        void operator=(unique_handler&) = delete;

        void operator=(
            unique_handler&& other_handler
        )
        {
            this->move_from_other(std::move(other_handler));
        }

        #pragma endregion


        #pragma region getters_and_setters

        #pragma endregion
    };
}


#endif