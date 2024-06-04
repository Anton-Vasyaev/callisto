#pragma once

// std
#include <vector>
#include <string>
// project
#include <callisto/framework/native/platform_detect.h>

// clang-format off

#ifdef CALLISTO_OS_WINDOWS 
#define CALLISTO_BEGIN_WMAIN                                            \
    int wmain(int argc, wchar_t** argv)                                 \
    {                                                                   \
        std::vector<std::wstring> command_line_arguments;               \
        for(int i = 0; i < argc; i++) command_line_arguments.push_back( \
            std::wstring(argv[i])                                       \
        );                                                                      
#endif
        



#define CALLISTO_END_WMAIN    \
    }

// clang-format on