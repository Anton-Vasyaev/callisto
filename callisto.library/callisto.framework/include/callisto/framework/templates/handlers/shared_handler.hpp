#ifndef SHARED_SCOPE_HANDLER_HPP
#define SHARED_SCOPE_HANDLER_HPP

// std
#include <utility>
#include <mutex>
// project
#include "default_disposer.hpp"


namespace callisto::framework
{
    template<
        typename _data_type,
        typename _disposer_type=default_disposer<_data_type>
    >
    class shared_handler
    {
    private:
        using data_type = _data_type;
        
        using disposer_type = _disposer_type;

        data_type data;

        disposer_type disposer;

        size_t* ref_counter = nullptr;

        std::mutex* mutex = nullptr;

        bool has_handler = false;


        #pragma region private_methods

        inline void destroy()
        {
            if (!(this->has_handler)) return;

            size_t current_counter = 0;
            {
                std::unique_lock<std::mutex> locker(*(this->mutex));
                (*(this->ref_counter))--;
                if (*(this->ref_counter) == 0)
                {
                    disposer(this->data);
                }

                current_counter = *(this->ref_counter);
            }
            if (current_counter == 0)
            {
                if (this->mutex != nullptr)
                {
                    delete this->mutex;
                    this->mutex = nullptr;
                }
                if (this->ref_counter != nullptr)
                {
                    delete this->ref_counter;
                    this->ref_counter = nullptr;
                }
            }
            this->has_handler = false;
        }

        inline void copy_from(
            shared_handler& other_handler
        )
        {
            std::unique_lock(*(other_handler.mutex));

            this->destroy();

            this->data = other_handler.data;
            this->ref_counter = other_handler.ref_counter;
            this->mutex = other_handler.mutex;
            this->has_handler = other_handler.has_handler;

            (*(this->ref_counter))++;
        }

        inline void move_from(
            shared_handler&& other_handler
        )
        {
            this->destroy();

            this->data = other_handler.data;
            this->ref_counter = other_handler.ref_counter;
            this->mutex = other_handler.mutex;
            this->has_handler = other_handler.has_handler;

            other_handler.ref_counter = nullptr;
            other_handler.mutex = nullptr;
            other_handler.has_handler = false;
        }

        inline void create_new(
            data_type data
        )
        {
            this->destroy();

            try
            {
                this->ref_counter = new size_t;
                this->mutex = new std::mutex();

                this->data = data;
            }
            catch (...)
            {
                if (this->ref_counter != nullptr) delete this->ref_counter;
                if (this->mutex != nullptr) delete this->mutex;

                throw;
            }

            (*(this->ref_counter)) = 1;
            this->data = data;
            this->has_handler = true;
        }

        #pragma endregion

    public:
        #pragma region construct_and_destruct

        shared_handler() { };

        shared_handler(
            data_type data
        )
        {
            this->create_new(data);
        }

        shared_handler(
            shared_handler& other_handler
        )
        {
            this->copy_from(other_handler);
        }

        shared_handler(
            shared_handler&& other_handler
        )
        {
            this->move_from(other_handler);
        }

        ~shared_handler()
        {
            this->destroy();
        }

        #pragma endregion


        #pragma region methods

        void reset(data_type data)
        {
            this->create_new(data);
        }

        #pragma endregion


        #pragma region operators

        shared_handler& operator=(shared_handler& other_handler)
        {
            this->copy_from(other_handler);

            return *this;
        }

        shared_handler& operator=(shared_handler&& other_handler)
        {
            this->move_from(std::move(other_handler));

            return *this;
        }

        #pragma endregion


        #pragma region getters_and_setters

        data_type& get_data()
        {
            return this->data;
        }

        const data_type& get_data() const
        {
            return this->data;
        }

        size_t count() const
        {
            return *(this->ref_counter);
        }

        bool has_handler_status() const
        {
            return this->has_handler;
        }

        #pragma endregion
    };
}

#endif