#pragma once

// std
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

namespace callisto::framework
{

template<typename char_type>
inline auto __table_printer_empty_str__();

template<>
inline auto __table_printer_empty_str__<char>()
{
    return "";
}

template<>
inline auto __table_printer_empty_str__<wchar_t>()
{
    return L"";
}

/// @brief Presents row of table printer.
/// @tparam _char_type Data type of char for std::basic_string.
template<typename _char_type>
class basic_table_printer_row
{
public:
    /// @brief Char type of std::basic_string using for printing.
    using char_type = _char_type;

    /// @brief Data type of std::basic_string using for printing.
    using string_type = std::basic_string<char_type>;

    /// @brief Data type of std::basic_stringstream using for printing.
    using stringstream_type = std::basic_stringstream<char_type>;

    /// @brief Data type of row that stored string values.
    using cells_array_type = std::vector<string_type>;

private:
    stringstream_type _ss;

    cells_array_type _cells;

    template<typename type>
    string_type to_string(const type& value)
    {
        _ss << value;
        auto data = _ss.str();
        _ss.str(__table_printer_empty_str__<char_type>());

        return data;
    }

    inline void move_from(basic_table_printer_row&& row)
    {
        _ss    = std::move(row._ss);
        _cells = std::move(row._cells);
    }

    inline void copy_from(const basic_table_printer_row& row)
    {
        _ss.str(__table_printer_empty_str__<char_type>());
        _ss << row._ss.str();

        _cells = row._cells;
    }

public:
    /// @brief Constructor basic_table_printer_row.
    inline basic_table_printer_row() {}

    /// @brief Copy-constructor of basic_table_printer_row.
    /// @param row Row that stored string values.
    inline basic_table_printer_row(const basic_table_printer_row& row) { copy_from(row); }

    /// @brief Move-constructor of basic_table_printer_row.
    /// @param row Row that stored string values.
    inline basic_table_printer_row(basic_table_printer_row&& row) { move_from(std::move(row)); }

    /// @brief Constructor of basic_table_printer_row.
    /// @param size Count of row values.
    basic_table_printer_row(size_t size) { _cells.resize(size); }

    /// @brief Cosntructor of basic_table_printer_row for variadic values.
    /// @tparam ...args_type Parameter pack type of variadic values.
    /// @param ...args Variadic values.
    template<typename... args_type>
    basic_table_printer_row(const args_type&... args)
    {
        ((_cells.push_back(this->to_string(args))), ...);
    }

    /// @brief Appends value to row.
    /// @tparam type Data type of value which support operator << for ostream.
    /// @param value Value.
    template<typename type>
    void append_cell(const type& value)
    {
        _ss << value;

        _cells.push_back(_ss.str());

        _ss.str(__table_printer_empty_str__<char_type>());
    }

    /// @brief Counts the values in row.
    /// @return Count.
    size_t size() const noexcept { return _cells.size(); }

    /// @brief Returns string present of cell in row.
    /// @param index Index of cell.
    /// @return String present.
    string_type& get_cell(size_t index) & noexcept { return _cells[index]; }

    /// @brief Returns const string present of cell in row.
    /// @param index Index of cell.
    /// @return String present.
    const string_type& get_cell(size_t index) const& noexcept { return _cells[index]; }

    /// @brief Returns reference to array of string cells.
    /// @return Array of string cells.
    cells_array_type& get_cells() & noexcept { return _cells; }

    /// @brief Returns const reference to array of string cells.
    /// @return Reference to array of string cells.
    const cells_array_type& get_cells() const& noexcept { return _cells; }

    /// @brief Copy-operator.
    /// @param row other row.
    /// @return Reference to *this.
    basic_table_printer_row& operator=(const basic_table_printer_row& row) { copy_from(row); }

    /// @brief Move-operator.
    /// @param row other row.
    /// @return Reference to *this.
    basic_table_printer_row& operator=(basic_table_printer_row&& row) { move_from(std::move(row)); }
};

/// @brief Provides formatting table-style printing.
/// @tparam _char_type Type of char.
template<typename _char_type>
class basic_table_printer
{
public:
    /// @brief Char type of std::basic_string using for printing.
    using char_type = _char_type;

    /// @brief Data type of row which stored cells strings.
    using row_type = basic_table_printer_row<char_type>;

    /// @brief Data type of std::basic_string using for printing.
    using string_type = typename row_type::string_type;

    /// @brief Data type of std::basic_stringstream using for printing.
    using stringstream_type = typename row_type::stringstream_type;

    /// @brief Data type of array of rows.
    using rows_array_type = std::vector<row_type>;

private:
    rows_array_type _rows;

    static std::vector<size_t> get_max_cells_sizes(const rows_array_type& table)
    {
        std::vector<size_t> max_cell_sizes;

        for (size_t row_i = 0; row_i < table.size(); row_i++)
        {
            auto& row = table[row_i].get_cells();
            if (row.size() > max_cell_sizes.size()) max_cell_sizes.resize(row.size());

            for (size_t cell_i = 0; cell_i < row.size(); cell_i++)
            {
                max_cell_sizes[cell_i] = std::max(max_cell_sizes[cell_i], row[cell_i].length());
            }
        }

        return std::move(max_cell_sizes);
    }

    template<typename buffer_type>
    static void set_space_buffer(buffer_type& buffer, size_t space_count = 1)
    {
        std::fill_n(std::begin(buffer), space_count, ' ');
        buffer[space_count] = 0;
    }

public:
    /// @brief Default constructor.
    basic_table_printer() = default;

    /// @brief Constructor. Constructs table with the given counts of rows.
    /// @param size Counts of rows.
    basic_table_printer(size_t size) { _rows.resize(size); }

    /// @brief Consturctor. Constructs table with rows listed via initializer list.
    /// @param rows_list
    basic_table_printer(std::initializer_list<row_type> rows_list)
    {
        for (auto& row : rows_list) { _rows.push_back(std::move(row)); }
    }

    /// @brief Appends new row to table.
    /// @param row Row of string cells.
    inline void append_row(const row_type& row) { _rows.push_back(row); }

    /// @brief Move-semantic append row to table.
    /// @param row Row of string cells.
    inline void append_row(row_type&& row) { _rows.push_back(std::move(row)); }

    /// @brief Returns reference to array of rows.
    /// @return Reference to array of rows.
    inline rows_array_type& get_rows() noexcept { return _rows; }

    /// @brief Returns const reference to array of rows.
    /// @return Const reference to array of rows.
    inline const rows_array_type& get_rows() const noexcept { return _rows; }

    /// @brief Returns reference to row by-index.
    /// @param index Index of row.
    /// @return Reference to row.
    inline row_type& get_row(size_t index) noexcept { return _rows[index]; }

    /// @brief Returns const reference to row by-index.
    /// @param index Index of row.
    /// @return Reference to row.
    inline const row_type& get_row(size_t index) const noexcept { return _rows[index]; }

    /// @brief Forms printing lines for table-formatting printing.
    /// @param space_count Count of space between string cells.
    /// @return Array of printing lines.
    std::vector<string_type> get_print_lines(size_t space_count) const
    {
        std::vector<string_type> lines;

        stringstream_type ss;

        auto   max_cell_sizes = basic_table_printer::get_max_cells_sizes(_rows);
        size_t max_cell_size  = 0;
        for (auto& cell_size : max_cell_sizes)
        {
            if (cell_size > max_cell_size) max_cell_size = cell_size;
        }
        max_cell_size += space_count;

        std::vector<char_type> space_buffer(max_cell_size);
        std::fill_n(std::begin(space_buffer), max_cell_size - 1, ' ');
        space_buffer[max_cell_size - 1]   = '\0';
        size_t prev_space_buffer_null_idx = max_cell_size - 1;

        for (auto& row : _rows)
        {
            for (size_t i = 0; i < row.size(); i++)
            {
                auto str_cell = row.get_cells()[i];

                auto added_space_count = max_cell_sizes[i] + space_count - str_cell.length();
                space_buffer[prev_space_buffer_null_idx] = ' ';
                space_buffer[added_space_count]          = '\0';
                prev_space_buffer_null_idx               = added_space_count;

                ss << str_cell;
                ss << (char_type*)space_buffer.data();
            }

            lines.push_back(std::move(ss.str()));
            ss.str(__table_printer_empty_str__<char_type>());
        }

        return std::move(lines);
    }
};

/// @brief Operator << of ostream and @see basic_table_printer
/// @tparam ostream_type Type of ostream.
/// @tparam char_type Char type of @see basic_table_printer.
/// @param stream ostream.
/// @param printer printer.
/// @return Reference to ostream.
template<typename ostream_type, typename char_type>
ostream_type& operator<<(ostream_type& stream, const basic_table_printer<char_type>& printer)
{
    auto lines = printer.get_print_lines(1);

    for (auto& line : lines) stream << line << "\n";

    return stream;
}

/// @brief Alias of @see basic_table_printer for char.
using table_printer = basic_table_printer<char>;

/// @brief Alias of @see basic_table_printer_row for char.
using table_printer_row = basic_table_printer_row<char>;

/// @brief Alias of @see basic_table_printer for wchar_t.
using wtable_printer = basic_table_printer<wchar_t>;

/// @brief Alias of @see basic_table_printer_row for wchar_t.
using wtable_printer_row = basic_table_printer_row<wchar_t>;

} // namespace callisto::framework