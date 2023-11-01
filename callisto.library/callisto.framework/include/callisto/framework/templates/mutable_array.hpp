#pragma once

// std
#include <cstddef>
#include <algorithm>

namespace callisto::framework
{
    template<typename type, size_t n>
    class mutable_array
    {
    public:
        using value_type = type;

        using iterator = value_type*;

        using const_iterator = const value_type*;

        using reverse_iterator = std::reverse_iterator<value_type*>;

        using const_reverse_iterator = std::reverse_iterator<const value_type*>;

        static const size_t array_size = n;

    private:
        value_type data_array[array_size];

        size_t mutable_size = 0;
        
    public:
        inline mutable_array() noexcept { }

        inline mutable_array(const mutable_array& array) noexcept
        {
            this->copy_from(array);
        }

        inline mutable_array(mutable_array&& array) noexcept
        {
            this->move_from(std::move(array));
        }


        // methods
        inline void copy_from(const mutable_array& array) noexcept
        {
            std::copy_n(array.data_array, array.mutable_size, this->data_array);
            this->mutable_size = array.mutable_size;
        }

        inline void move_from(mutable_array&& array) noexcept
        {
            this->copy_from(array);
            array.mutable_size = 0;
        }

        void resize(size_t new_size)
        {
            if(new_size > array_size) throw std::bad_alloc(
                "failed in mutable_array: resize > static_size"
            );
            this->mutable_size = new_size;
        }


        // getters and setters
        inline size_t size() const noexcept { return this->mutable_size; }


        inline value_type* data() noexcept { return this->data_array; }

        inline const value_type* data() const noexcept { return this->data_array; }


        inline iterator begin() noexcept { return this->data_array; }

        inline const_iterator begin() const noexcept { return this->data_array; }


        inline iterator end() noexcept { return this->data_array + this->mutable_size; }

        inline const_iterator end() const noexcept { return this->data_array + this->mutable_size; }


        inline reverse_iterator rbegin() noexcept
        {
            return std::reverse_iterator<value_type*>(this->data_array + this->mutable_size);
        }

        inline const_reverse_iterator rbegin() const noexcept
        {
            return std::reverse_iterator<const value_type*>(this->data_array + this->mutable_size);
        }


        inline reverse_iterator rend() noexcept
        {
            return std::reverse_iterator<value_type*>(this->data_array);
        }

        inline const_reverse_iterator rend() const noexcept
        {
            return std::reverse_iterator<const value_type*>(this->data_array);
        }

        // operators
        inline const mutable_array& operator=(const mutable_array& array) noexcept
        {
            this->copy_from(array);

            return *this;
        }

        inline const mutable_array& operator=(mutable_array&& array) noexcept
        {
            this->move_from(std::move(array));

            return *this;
        }

        inline value_type& operator[](std::size_t index) noexcept
        {
            return this->data_array[index];
        }

        inline const value_type& operator[](std::size_t index) const noexcept
        {
            return this->data_array[index];
        }
    };
}