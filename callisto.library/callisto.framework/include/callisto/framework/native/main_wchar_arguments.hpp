#pragma once

// std
#include <vector>
#include <string>
// project
#include <callisto/framework/native/platform_detect.h>

// clang-format off

#ifdef CALLISTO_OS_WINDOWS 
#define BEGIN_MAIN_WCHAR_ARGUMENTS                                      \
    int wmain(int argc, wchar_t** argv)                                 \
    {                                                                   \
        std::vector<std::wstring> command_line_arguments;               \
        for(int i = 0; i < argc; i++) command_line_arguments.push_back( \
            std::wstring(argv[i])                                       \
        );                                                                  
#endif
        



#define END_MAIN_WCHAR_ARGUMENTS    \
    }

// clang-format on