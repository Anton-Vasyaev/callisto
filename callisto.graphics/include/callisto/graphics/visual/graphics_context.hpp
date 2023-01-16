#pragma once

// std
#include <unordered_map>
#include <string>
#include <memory>
// project
#include "i_main_context.hpp"

namespace callisto::graphics
{

class graphics_context
{
private:
    // data
    std::unordered_map<std::string, std::unique_ptr<i_main_context>> contexts;

public:
    // construct and destruct
    graphics_context();

    // deleted
    graphics_context(const graphics_context&) = delete;

    graphics_context& operator=(graphics_context&) = delete;

    // methods
    i_main_context& get_context(const char* context_name);
};

} // namespace callisto::graphics