#pragma once

// std
#include <iostream>

namespace callisto::framework
{
/// @brief Provides print sequence to ostream with operator <<
/// @tparam type Data type of sequence type.
template<typename type>
class sequence_printer
{
private:
    const type& _sequential;

    sequence_printer() = delete;

public:
    /// @brief Creates @see sequence_printer.
    /// @param sequential sequence.
    sequence_printer(const type& sequential) : _sequential(sequential) {}

    /// @brief Operator << of ostream and sequence_printer.
    /// @tparam ostream_type Data type of ostream.
    /// @tparam type2 Value type of sequence.
    /// @param os ostream.
    /// @param sp sequence_printer.
    /// @return ostream reference.
    template<typename ostream_type, typename type2>
    friend ostream_type& operator<<(ostream_type& os, const sequence_printer<type2>& sp);
};

template<typename type>
sequence_printer(type) -> sequence_printer<type>;

template<typename ostream_type, typename type2>
ostream_type& operator<<(ostream_type& os, const sequence_printer<type2>& sp)
{
    os << "[";
    bool first = true;
    for (auto& element : sp._sequential)
    {
        if (!first) os << " ";
        os << element;

        if (first) first = false;
    }
    os << "]";

    return os;
}

} // namespace callisto::framework
