#pragma once

// std
#include <vector>
#include <string>
// project
#include <callisto/framework/native/platform_detect.h>

// clang-format off

#ifdef CALLISTO_OS_WINDOWS 

#define CALLISTO_WMAIN(main_func_name)                                  \
    int wmain(int argc, wchar_t** argv)                                 \
    {                                                                   \
        std::vector<std::wstring> command_line_arguments;               \
        for(int i = 0; i < argc; i++) command_line_arguments.push_back( \
            std::wstring(argv[i])                                       \
        );                                                              \
                                                                        \
        auto code = main_func_name(command_line_arguments);             \
        return code;                                                    \
    }                                                                   \
    
#endif

// clang-format on