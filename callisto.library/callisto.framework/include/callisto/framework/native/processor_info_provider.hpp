#pragma once

// std
#include <string>
#include <memory>
// project
#include <callisto/framework/native/platform_detect.h>

#include <callisto/framework/types/lifetime.hpp>
#include <callisto/framework/types/singleton.hpp>

namespace callisto::framework
{

/// @brief Provide information about CPU using cpuid command.
class processor_info_provider : public singleton<processor_info_provider>
{
    friend class singleton<processor_info_provider>;

    struct inner_data;

    std::unique_ptr<inner_data> __inner_data_ptr;

    processor_info_provider();

public:
    ~processor_info_provider();

    CALLISTO_LIFETIME_REFERENCE(processor_info_provider);

    bool is_init() noexcept;

    const std::string& get_not_init_error_message() noexcept;

    const std::string& get_vendor_name() noexcept;

    const std::string& get_code_name() noexcept;

    const std::string& get_brand_name() noexcept;

    int32_t get_num_cores() noexcept;

    int32_t get_num_logical_cpus() noexcept;

    int32_t get_total_logical_cpus() noexcept;

    int32_t get_l1_data_cache() noexcept;

    int32_t get_l1_instruction_cache() noexcept;

    int32_t get_l2_cache() noexcept;

    int32_t get_l3_cache() noexcept;

    int32_t get_l4_cache() noexcept;

    int32_t get_l1_assoc() noexcept;

    int32_t get_l1_data_assoc() noexcept;

    int32_t get_l1_instruction_assoc() noexcept;

    int32_t get_l2_assoc() noexcept;

    int32_t get_l3_assoc() noexcept;

    int32_t get_l4_assoc() noexcept;

    int32_t get_l1_cacheline() noexcept;

    int32_t get_l1_data_cacheline() noexcept;

    int32_t get_l1_instruction_cacheline() noexcept;

    int32_t get_l2_cacheline() noexcept;

    int32_t get_l3_cacheline() noexcept;

    int32_t get_l4_cacheline() noexcept;

#pragma endregion

#pragma region cpu_x86
#ifdef CALLISTO_ARCHITECTURE_FAMILY_X86

    bool get_feature_mmx() noexcept;

    bool get_feature_sse() noexcept;

    bool get_feature_sse_2() noexcept;

    bool get_feature_ssse_3() noexcept;

    bool get_feature_sse_4_1() noexcept;

    bool get_feature_sse_4_2() noexcept;

    bool get_feature_avx() noexcept;

    bool get_feature_mmxext() noexcept;

    bool get_feature_3dnow() noexcept;

    bool get_feature_3dnow_ext() noexcept;

    bool get_feature_sse_4a() noexcept;

    bool get_feature_3dnow_prefetch() noexcept;

    bool get_feature_fma_3() noexcept;

    bool get_feature_fma_4() noexcept;

    bool get_feature_avx_2() noexcept;

    bool get_feature_avx_512_f() noexcept;

    bool get_feature_avx_512_dq() noexcept;

    bool get_feature_avx_512_pf() noexcept;

    bool get_feature_avx_512_er() noexcept;

    bool get_feature_avx_512_cd() noexcept;

    bool get_feature_avx_512_bw() noexcept;

    bool get_feature_avx_512_vl() noexcept;

    bool get_feature_avx_512_vnni() noexcept;

    bool get_feature_avx_512_vbmi() noexcept;

    bool get_feature_avx_512_vbmi_2() noexcept;

#endif
#pragma endregion
};

} // namespace callisto::framework