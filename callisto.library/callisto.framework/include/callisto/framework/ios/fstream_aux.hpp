#pragma once

#include <fstream>

namespace callisto::framework
{

/// @brief Presents auxiliary functions for filestream classes
struct fstream_aux
{

    /// @brief Returns size of file handling by filestream.
    /// @tparam fstream_type Type of filestream.
    /// @param fstream File stream.
    /// @return Size of file.
    template<typename fstream_type>
    static size_t size_of_file(fstream_type& fstream)
    {
        auto current_pos = fstream.tellg();
        fstream.seekg(0, std::ios::end);
        size_t length = fstream.tellg();
        fstream.seekg(0, current_pos);

        return length;
    }
};

} // namespace callisto::framework
