// parent header
#include <callisto/framework/native/processor_info.hpp>
// std
#include <stdexcept>
// 3rd party
#include <libcpuid/libcpuid.h>
// project
#include <callisto/framework/string.hpp>
#include <callisto/framework/exception.hpp>

namespace callisto::framework
{

#pragma region data

#pragma region cpu_standard

std::string vendor_name;

std::string code_name;

std::string brand_name;

int32_t num_cores = -1;

int32_t num_logical_cpus = -1;

int32_t total_logical_cpus = -1;

int32_t l1_data_cache = -1;

int32_t l1_instruction_cache = -1;

int32_t l2_cache = -1;

int32_t l3_cache = -1;

int32_t l4_cache = -1;

int32_t l1_assoc = -1;

int32_t l1_data_assoc = -1;

int32_t l1_instruction_assoc = -1;

int32_t l2_assoc = -1;

int32_t l3_assoc = -1;

int32_t l4_assoc = -1;

int32_t l1_cacheline = -1;

int32_t l1_data_cacheline = -1;

int32_t l1_instruction_cacheline = -1;

int32_t l2_cacheline = -1;

int32_t l3_cacheline = -1;

int32_t l4_cacheline = -1;

#pragma endregion

#pragma region cpu_x86

bool feature_mmx = false;

bool feature_sse = false;

bool feature_sse_2 = false;

bool feature_ssse_3 = false;

bool feature_sse_4_1 = false;

bool feature_sse_4_2 = false;

bool feature_avx = false;

bool feature_mmxext = false;

bool feature_3dnow = false;

bool feature_3dnow_ext = false;

bool feature_sse_4a = false;

bool feature_3dnow_prefetch = false;

bool feature_fma_3 = false;

bool feature_fma_4 = false;

bool feature_avx_2 = false;

bool feature_avx_512_f = false;

bool feature_avx_512_dq = false;

bool feature_avx_512_pf = false;

bool feature_avx_512_er = false;

bool feature_avx_512_cd = false;

bool feature_avx_512_bw = false;

bool feature_avx_512_vl = false;

bool feature_avx_512_vnni = false;

bool feature_avx_512_vbmi = false;

bool feature_avx_512_vbmi_2 = false;

#pragma endregion

#pragma endregion

#pragma region init

processor_info::__static_init__::__static_init__()
{

#pragma region cpu_standard

    if (!cpuid_present())
    {
        throw std::runtime_error("CPU Id not present\n");
    }

    cpu_raw_data_t raw;
    cpu_id_t       data;

    if (cpuid_get_raw_data(&raw) < 0)
    {
        throw runtime_exception(
        ) << error_tag_message(_bs("Cannot get CPUID raw data. Error:", cpuid_error(), "."));
    }

    if (cpu_identify(&raw, &data) < 0)
    {
        throw runtime_exception(
        ) << error_tag_message(_bs("CPU identification failed. Error:", cpuid_error(), "."));
    }

    vendor_name = data.vendor_str;

    code_name = data.cpu_codename;

    brand_name = data.brand_str;

    num_cores = data.num_cores;

    num_logical_cpus = data.num_logical_cpus;

    total_logical_cpus;

    l1_data_cache = data.l1_data_cache;

    l1_instruction_cache = data.l1_instruction_cache;

    l2_cache = data.l2_cache;

    l3_cache = data.l3_cache;

    l4_cache = data.l4_cache;

    l1_assoc = data.l1_assoc;

    l1_data_assoc = data.l1_data_cache;

    l1_instruction_assoc = data.l1_instruction_assoc;

    l2_assoc = data.l2_assoc;

    l3_assoc = data.l3_assoc;

    l4_assoc = data.l4_assoc;

    l1_cacheline = data.l1_cacheline;

    l1_data_cacheline = data.l1_data_cacheline;

    l1_instruction_cacheline = data.l1_instruction_cacheline;

    l2_cacheline = data.l2_cacheline;

    l3_cacheline = data.l3_cacheline;

    l4_cacheline = data.l4_cacheline;

#pragma endregion

#ifdef CALLISTO_ARCHITECTURE_FAMILY_X86

    feature_mmx = data.flags[CPU_FEATURE_MMX];

    feature_sse = data.flags[CPU_FEATURE_SSE];

    feature_sse = data.flags[CPU_FEATURE_SSE2];

    feature_ssse_3 = data.flags[CPU_FEATURE_SSSE3];

    feature_sse_4_1 = data.flags[CPU_FEATURE_SSE4_1];

    feature_sse_4_2 = data.flags[CPU_FEATURE_SSE4_2];

    feature_avx = data.flags[CPU_FEATURE_AVX];

    feature_mmxext = data.flags[CPU_FEATURE_MMXEXT];

    feature_3dnow = data.flags[CPU_FEATURE_3DNOW];

    feature_3dnow_ext = data.flags[CPU_FEATURE_3DNOWEXT];

    feature_sse_4a = data.flags[CPU_FEATURE_SSE4A];

    feature_3dnow_prefetch = data.flags[CPU_FEATURE_3DNOWPREFETCH];

    feature_fma_3 = data.flags[CPU_FEATURE_FMA3];

    feature_fma_4 = data.flags[CPU_FEATURE_FMA4];

    feature_avx_2 = data.flags[CPU_FEATURE_AVX2];

    feature_avx_512_f = data.flags[CPU_FEATURE_AVX512F];

    feature_avx_512_dq = data.flags[CPU_FEATURE_AVX512DQ];

    feature_avx_512_pf = data.flags[CPU_FEATURE_AVX512PF];

    feature_avx_512_er = data.flags[CPU_FEATURE_AVX512ER];

    feature_avx_512_cd = data.flags[CPU_FEATURE_AVX512CD];

    feature_avx_512_bw = data.flags[CPU_FEATURE_AVX512BW];

    feature_avx_512_vl = data.flags[CPU_FEATURE_AVX512VL];

    feature_avx_512_vnni = data.flags[CPU_FEATURE_AVX512VNNI];

    feature_avx_512_vbmi = data.flags[CPU_FEATURE_AVX512VBMI];

    feature_avx_512_vbmi_2 = data.flags[CPU_FEATURE_AVX512VBMI2];

#endif
}

processor_info::__static_init__ processor_info::__static_initializer__;

#pragma endregion

#pragma region getters

#pragma region cpu_standard

std::string processor_info::get_vendor_name() noexcept { return vendor_name; }

std::string processor_info::get_code_name() noexcept { return code_name; }

std::string processor_info::get_brand_name() noexcept { return brand_name; }

int32_t processor_info::get_num_cores() noexcept { return num_cores; }

int32_t processor_info::get_num_logical_cpus() noexcept { return num_logical_cpus; }

int32_t processor_info::get_total_logical_cpus() noexcept { return total_logical_cpus; }

int32_t processor_info::get_l1_data_cache() noexcept { return l1_data_cache; }

int32_t processor_info::get_l1_instruction_cache() noexcept { return l1_instruction_cache; }

int32_t processor_info::get_l2_cache() noexcept { return l2_cache; }

int32_t processor_info::get_l3_cache() noexcept { return l3_cache; }

int32_t processor_info::get_l4_cache() noexcept { return l4_cache; }

int32_t processor_info::get_l1_assoc() noexcept { return l1_assoc; }

int32_t processor_info::get_l1_data_assoc() noexcept { return l1_data_assoc; }

int32_t processor_info::get_l1_instruction_assoc() noexcept { return l1_instruction_assoc; }

int32_t processor_info::get_l2_assoc() noexcept { return l2_assoc; }

int32_t processor_info::get_l3_assoc() noexcept { return l3_assoc; }

int32_t processor_info::get_l4_assoc() noexcept { return l4_assoc; }

int32_t processor_info::get_l1_cacheline() noexcept { return l1_cacheline; }

int32_t processor_info::get_l1_data_cacheline() noexcept { return l1_data_cacheline; }

int32_t processor_info::get_l1_instruction_cacheline() noexcept { return l1_instruction_cacheline; }

int32_t processor_info::get_l2_cacheline() noexcept { return l2_cacheline; }

int32_t processor_info::get_l3_cacheline() noexcept { return l3_cacheline; }

int32_t processor_info::get_l4_cacheline() noexcept { return l4_cacheline; }

#pragma endregion

#ifdef CALLISTO_ARCHITECTURE_FAMILY_X86

bool processor_info::get_feature_mmx() noexcept
{
    return feature_mmx;
    feature_mmx;
}

bool processor_info::get_feature_sse() noexcept { return feature_sse; }

bool processor_info::get_feature_sse_2() noexcept { return feature_sse_2; }

bool processor_info::get_feature_ssse_3() noexcept { return feature_ssse_3; }

bool processor_info::get_feature_sse_4_1() noexcept { return feature_sse_4_1; }

bool processor_info::get_feature_sse_4_2() noexcept { return feature_sse_4_2; }

bool processor_info::get_feature_avx() noexcept { return feature_avx; }

bool processor_info::get_feature_mmxext() noexcept { return feature_mmxext; }

bool processor_info::get_feature_3dnow() noexcept { return feature_3dnow; }

bool processor_info::get_feature_3dnow_ext() noexcept { return feature_3dnow_ext; }

bool processor_info::get_feature_sse_4a() noexcept { return feature_sse_4a; }

bool processor_info::get_feature_3dnow_prefetch() noexcept { return feature_3dnow_prefetch; }

bool processor_info::get_feature_fma_3() noexcept { return feature_fma_3; }

bool processor_info::get_feature_fma_4() noexcept { return feature_fma_4; }

bool processor_info::get_feature_avx_2() noexcept { return feature_avx_2; }

bool processor_info::get_feature_avx_512_f() noexcept { return feature_avx_512_f; }

bool processor_info::get_feature_avx_512_dq() noexcept { return feature_avx_512_dq; }

bool processor_info::get_feature_avx_512_pf() noexcept { return feature_avx_512_pf; }

bool processor_info::get_feature_avx_512_er() noexcept { return feature_avx_512_er; }

bool processor_info::get_feature_avx_512_cd() noexcept { return feature_avx_512_cd; }

bool processor_info::get_feature_avx_512_bw() noexcept { return feature_avx_512_bw; }

bool processor_info::get_feature_avx_512_vl() noexcept { return feature_avx_512_vl; }

bool processor_info::get_feature_avx_512_vnni() noexcept { return feature_avx_512_vnni; }

bool processor_info::get_feature_avx_512_vbmi() noexcept { return feature_avx_512_vbmi; }

bool processor_info::get_feature_avx_512_vbmi_2() noexcept { return feature_avx_512_vbmi_2; }

#endif

#pragma endregion
} // namespace callisto::framework