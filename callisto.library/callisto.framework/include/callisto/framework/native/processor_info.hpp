#pragma once

// std
#include <string>
// project
#include <callisto/framework/native/platform_detect.h>

namespace callisto::framework
{

/// @brief Provide information about CPU using cpuid command.
class processor_info
{
public:
    static std::string get_vendor_name() noexcept;

    static std::string get_code_name() noexcept;

    static std::string get_brand_name() noexcept;

    static int32_t get_num_cores() noexcept;

    static int32_t get_num_logical_cpus() noexcept;

    static int32_t get_total_logical_cpus() noexcept;

    static int32_t get_l1_data_cache() noexcept;

    static int32_t get_l1_instruction_cache() noexcept;

    static int32_t get_l2_cache() noexcept;

    static int32_t get_l3_cache() noexcept;

    static int32_t get_l4_cache() noexcept;

    static int32_t get_l1_assoc() noexcept;

    static int32_t get_l1_data_assoc() noexcept;

    static int32_t get_l1_instruction_assoc() noexcept;

    static int32_t get_l2_assoc() noexcept;

    static int32_t get_l3_assoc() noexcept;

    static int32_t get_l4_assoc() noexcept;

    static int32_t get_l1_cacheline() noexcept;

    static int32_t get_l1_data_cacheline() noexcept;

    static int32_t get_l1_instruction_cacheline() noexcept;

    static int32_t get_l2_cacheline() noexcept;

    static int32_t get_l3_cacheline() noexcept;

    static int32_t get_l4_cacheline() noexcept;

#pragma endregion

#pragma region cpu_x86
#ifdef CALLISTO_ARCHITECTURE_FAMILY_X86

    static bool get_feature_mmx() noexcept;

    static bool get_feature_sse() noexcept;

    static bool get_feature_sse_2() noexcept;

    static bool get_feature_ssse_3() noexcept;

    static bool get_feature_sse_4_1() noexcept;

    static bool get_feature_sse_4_2() noexcept;

    static bool get_feature_avx() noexcept;

    static bool get_feature_mmxext() noexcept;

    static bool get_feature_3dnow() noexcept;

    static bool get_feature_3dnow_ext() noexcept;

    static bool get_feature_sse_4a() noexcept;

    static bool get_feature_3dnow_prefetch() noexcept;

    static bool get_feature_fma_3() noexcept;

    static bool get_feature_fma_4() noexcept;

    static bool get_feature_avx_2() noexcept;

    static bool get_feature_avx_512_f() noexcept;

    static bool get_feature_avx_512_dq() noexcept;

    static bool get_feature_avx_512_pf() noexcept;

    static bool get_feature_avx_512_er() noexcept;

    static bool get_feature_avx_512_cd() noexcept;

    static bool get_feature_avx_512_bw() noexcept;

    static bool get_feature_avx_512_vl() noexcept;

    static bool get_feature_avx_512_vnni() noexcept;

    static bool get_feature_avx_512_vbmi() noexcept;

    static bool get_feature_avx_512_vbmi_2() noexcept;

#endif
#pragma endregion

    friend class __static_init__;

    static class __static_init__
    {
    public:
        __static_init__();

    } __static_initializer__;
};

} // namespace callisto::framework