#pragma once

// DETECT OS
#if defined(_WIN64) || defined(_WIN32)
    #define CALLISTO_OS_WINDOWS
    #define CALLISTO_OS_NAME "Windows"
#elif defined(__linux__)
    #define CALLISTO_OS_LINUX
    #define CALLISTO_OS_NAME "Linux"
#endif

#if defined(CALLISTO_OS_WINDOWS)
    #define CALLISTO_OS_FAMILY_NT
    #define CALLISTO_OS_FAMILY_NAME "NT"
#elif defined(CALLISTO_OS_LINUX)
    #define CALLISTO_OS_FAMILY_UNIX
    #define CALLISTO_OS_FAMILY_NAME "Unix"
#endif

//
// DETECT ARCHITECTURE
//
#if defined(__i386__) || defined(_M_IX86) || defined(_MI86)
    #define CALLISTO_ARCHITECTURE_I386
    #define CALLISTO_ARCHITECTURE_NAME "i386"
#elif defined(_M_AMD64) || defined(__amd64__)
    #define CALLISTO_ARCHITECTURE_AMD64
    #define CALLISTO_ARCHITECTURE_NAME "amd64"
#endif

#if defined(CALLISTO_ARCHITECTURE_I386) || defined(CALLISTO_ARCHITECTURE_AMD64)
    #define CALLISTO_ARCHITECTURE_FAMILY_X86
    #define CALLISTO_ARCHITECTURE_FAMILY_NAME "x86"
#endif

// DETECT BIT DESIGN
#if defined(CALLISTO_OS_FAMILY_UNIX)
    #if defined(__amd64__)
        #define CALLISTO_BIT_DESIGN_X64
    #else
        #define CALLISTO_BIT_DESIGN_X32
    #endif
#endif

#if defined(CALLISTO_OS_FAMILY_NT)
    #if defined(_WIN64)
        #define CALLISTO_BIT_DESIGN_X64
    #else
        #define CALLISTO_BIT_DESIGN_X32
    #endif
#endif

#if defined(CALLISTO_BIT_DESIGN_X32)
    #define CALLISTO_BIT_DESIGN_NAME "x32"
#elif defined(CALLISTO_BIT_DESIGN_X64)
    #define CALLISTO_BIT_DESIGN_NAME "x64"
#endif