// parent header
#include <callisto/framework/memory/aligned.hpp>
// std
#include <cstdint>
#include <cstdio>
#include <cstdlib>
// 3rd party
// project
#include <callisto/framework/native/platform_detect.h>

namespace callisto::framework
{
#ifdef CALLISTO_OS_WINDOWS

void* mem_aligned_alloc(size_t size, size_t aligned_size) noexcept
{
    return _aligned_malloc(size, aligned_size);
}

void mem_aligned_free(void* pointer) noexcept
{
    _aligned_free(pointer);
}
#endif

#ifdef CALLISTO_OS_LINUX

void* mem_aligned_alloc(size_t size, size_t aligned_size) noexcept
{
    return ::aligned_alloc(size, aligned_size);
}

void mem_aligned_free(void* pointer) noexcept
{
    ::free(pointer);
}

#endif

}