// parent header
#include <callisto/framework/native/processor_info_provider.hpp>
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

struct processor_info_provider::inner_data
{

    bool is_init_flag = false;

    std::string not_init_error_message;

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
};

#pragma endregion

#pragma region construct_and_destruct

processor_info_provider::processor_info_provider()
{
    __inner_data_ptr = std::make_unique<inner_data>();

#pragma region cpu_standard

    std::string not_init_error_message;
    if (!static_cast<bool>(cpuid_present()))
    {
        not_init_error_message = "CPU Id not present\n";
        return;
    }

    cpu_raw_data_t raw;
    cpu_id_t       data;

    if (cpuid_get_raw_data(&raw) < 0)
    {
        not_init_error_message = _bs("Cannot get CPUID raw data. Error:", cpuid_error(), ".");
        return;
    }

    if (cpu_identify(&raw, &data) < 0)
    {
        not_init_error_message = _bs("CPU identification failed. Error:", cpuid_error(), ".");
        return;
    }

    if (!not_init_error_message.empty())
    {
        CALLISTO_THROW_EXCEPTION(runtime_exception())
            << error_tag_message(std::move(not_init_error_message));
    }

    // Initialize cpu data

    __inner_data_ptr->vendor_name = data.vendor_str;

    __inner_data_ptr->code_name = data.cpu_codename;

    __inner_data_ptr->brand_name = data.brand_str;

    __inner_data_ptr->num_cores = data.num_cores;

    __inner_data_ptr->num_logical_cpus = data.num_logical_cpus;

    __inner_data_ptr->total_logical_cpus = data.total_logical_cpus;

    __inner_data_ptr->l1_data_cache = data.l1_data_cache;

    __inner_data_ptr->l1_instruction_cache = data.l1_instruction_cache;

    __inner_data_ptr->l2_cache = data.l2_cache;

    __inner_data_ptr->l3_cache = data.l3_cache;

    __inner_data_ptr->l4_cache = data.l4_cache;

    __inner_data_ptr->l1_assoc = data.l1_assoc;

    __inner_data_ptr->l1_data_assoc = data.l1_data_cache;

    __inner_data_ptr->l1_instruction_assoc = data.l1_instruction_assoc;

    __inner_data_ptr->l2_assoc = data.l2_assoc;

    __inner_data_ptr->l3_assoc = data.l3_assoc;

    __inner_data_ptr->l4_assoc = data.l4_assoc;

    __inner_data_ptr->l1_cacheline = data.l1_cacheline;

    __inner_data_ptr->l1_data_cacheline = data.l1_data_cacheline;

    __inner_data_ptr->l1_instruction_cacheline = data.l1_instruction_cacheline;

    __inner_data_ptr->l2_cacheline = data.l2_cacheline;

    __inner_data_ptr->l3_cacheline = data.l3_cacheline;

    __inner_data_ptr->l4_cacheline = data.l4_cacheline;

#pragma endregion

#ifdef CALLISTO_ARCHITECTURE_FAMILY_X86

    __inner_data_ptr->feature_mmx = static_cast<bool>(data.flags[CPU_FEATURE_MMX]);

    __inner_data_ptr->feature_sse = static_cast<bool>(data.flags[CPU_FEATURE_SSE]);

    __inner_data_ptr->feature_sse = static_cast<bool>(data.flags[CPU_FEATURE_SSE2]);

    __inner_data_ptr->feature_ssse_3 = static_cast<bool>(data.flags[CPU_FEATURE_SSSE3]);

    __inner_data_ptr->feature_sse_4_1 = static_cast<bool>(data.flags[CPU_FEATURE_SSE4_1]);

    __inner_data_ptr->feature_sse_4_2 = static_cast<bool>(data.flags[CPU_FEATURE_SSE4_2]);

    __inner_data_ptr->feature_avx = static_cast<bool>(data.flags[CPU_FEATURE_AVX]);

    __inner_data_ptr->feature_mmxext = static_cast<bool>(data.flags[CPU_FEATURE_MMXEXT]);

    __inner_data_ptr->feature_3dnow = static_cast<bool>(data.flags[CPU_FEATURE_3DNOW]);

    __inner_data_ptr->feature_3dnow_ext = static_cast<bool>(data.flags[CPU_FEATURE_3DNOWEXT]);

    __inner_data_ptr->feature_sse_4a = static_cast<bool>(data.flags[CPU_FEATURE_SSE4A]);

    __inner_data_ptr->feature_3dnow_prefetch
        = static_cast<bool>(data.flags[CPU_FEATURE_3DNOWPREFETCH]);

    __inner_data_ptr->feature_fma_3 = static_cast<bool>(data.flags[CPU_FEATURE_FMA3]);

    __inner_data_ptr->feature_fma_4 = static_cast<bool>(data.flags[CPU_FEATURE_FMA4]);

    __inner_data_ptr->feature_avx_2 = static_cast<bool>(data.flags[CPU_FEATURE_AVX2]);

    __inner_data_ptr->feature_avx_512_f = static_cast<bool>(data.flags[CPU_FEATURE_AVX512F]);

    __inner_data_ptr->feature_avx_512_dq = static_cast<bool>(data.flags[CPU_FEATURE_AVX512DQ]);

    __inner_data_ptr->feature_avx_512_pf = static_cast<bool>(data.flags[CPU_FEATURE_AVX512PF]);

    __inner_data_ptr->feature_avx_512_er = static_cast<bool>(data.flags[CPU_FEATURE_AVX512ER]);

    __inner_data_ptr->feature_avx_512_cd = static_cast<bool>(data.flags[CPU_FEATURE_AVX512CD]);

    __inner_data_ptr->feature_avx_512_bw = static_cast<bool>(data.flags[CPU_FEATURE_AVX512BW]);

    __inner_data_ptr->feature_avx_512_vl = static_cast<bool>(data.flags[CPU_FEATURE_AVX512VL]);

    __inner_data_ptr->feature_avx_512_vnni = static_cast<bool>(data.flags[CPU_FEATURE_AVX512VNNI]);

    __inner_data_ptr->feature_avx_512_vbmi = static_cast<bool>(data.flags[CPU_FEATURE_AVX512VBMI]);

    __inner_data_ptr->feature_avx_512_vbmi_2
        = static_cast<bool>(data.flags[CPU_FEATURE_AVX512VBMI2]);

#endif
}

processor_info_provider::~processor_info_provider() {}

#pragma endregion

#pragma region getters

const std::string& processor_info_provider::get_not_init_error_message() noexcept
{
    return __inner_data_ptr->not_init_error_message;
}

#pragma region cpu_standard

const std::string& processor_info_provider::get_vendor_name() noexcept
{
    return __inner_data_ptr->vendor_name;
}

const std::string& processor_info_provider::get_code_name() noexcept
{
    return __inner_data_ptr->code_name;
}

const std::string& processor_info_provider::get_brand_name() noexcept
{
    return __inner_data_ptr->brand_name;
}

int32_t processor_info_provider::get_num_cores() noexcept { return __inner_data_ptr->num_cores; }

int32_t processor_info_provider::get_num_logical_cpus() noexcept
{
    return __inner_data_ptr->num_logical_cpus;
}

int32_t processor_info_provider::get_total_logical_cpus() noexcept
{
    return __inner_data_ptr->total_logical_cpus;
}

int32_t processor_info_provider::get_l1_data_cache() noexcept
{
    return __inner_data_ptr->l1_data_cache;
}

int32_t processor_info_provider::get_l1_instruction_cache() noexcept
{
    return __inner_data_ptr->l1_instruction_cache;
}

int32_t processor_info_provider::get_l2_cache() noexcept { return __inner_data_ptr->l2_cache; }

int32_t processor_info_provider::get_l3_cache() noexcept { return __inner_data_ptr->l3_cache; }

int32_t processor_info_provider::get_l4_cache() noexcept { return __inner_data_ptr->l4_cache; }

int32_t processor_info_provider::get_l1_assoc() noexcept { return __inner_data_ptr->l1_assoc; }

int32_t processor_info_provider::get_l1_data_assoc() noexcept
{
    return __inner_data_ptr->l1_data_assoc;
}

int32_t processor_info_provider::get_l1_instruction_assoc() noexcept
{
    return __inner_data_ptr->l1_instruction_assoc;
}

int32_t processor_info_provider::get_l2_assoc() noexcept { return __inner_data_ptr->l2_assoc; }

int32_t processor_info_provider::get_l3_assoc() noexcept { return __inner_data_ptr->l3_assoc; }

int32_t processor_info_provider::get_l4_assoc() noexcept { return __inner_data_ptr->l4_assoc; }

int32_t processor_info_provider::get_l1_cacheline() noexcept
{
    return __inner_data_ptr->l1_cacheline;
}

int32_t processor_info_provider::get_l1_data_cacheline() noexcept
{
    return __inner_data_ptr->l1_data_cacheline;
}

int32_t processor_info_provider::get_l1_instruction_cacheline() noexcept
{
    return __inner_data_ptr->l1_instruction_cacheline;
}

int32_t processor_info_provider::get_l2_cacheline() noexcept
{
    return __inner_data_ptr->l2_cacheline;
}

int32_t processor_info_provider::get_l3_cacheline() noexcept
{
    return __inner_data_ptr->l3_cacheline;
}

int32_t processor_info_provider::get_l4_cacheline() noexcept
{
    return __inner_data_ptr->l4_cacheline;
}

#pragma endregion

#ifdef CALLISTO_ARCHITECTURE_FAMILY_X86

bool processor_info_provider::get_feature_mmx() noexcept { return __inner_data_ptr->feature_mmx; }

bool processor_info_provider::get_feature_sse() noexcept { return __inner_data_ptr->feature_sse; }

bool processor_info_provider::get_feature_sse_2() noexcept
{
    return __inner_data_ptr->feature_sse_2;
}

bool processor_info_provider::get_feature_ssse_3() noexcept
{
    return __inner_data_ptr->feature_ssse_3;
}

bool processor_info_provider::get_feature_sse_4_1() noexcept
{
    return __inner_data_ptr->feature_sse_4_1;
}

bool processor_info_provider::get_feature_sse_4_2() noexcept
{
    return __inner_data_ptr->feature_sse_4_2;
}

bool processor_info_provider::get_feature_avx() noexcept { return __inner_data_ptr->feature_avx; }

bool processor_info_provider::get_feature_mmxext() noexcept
{
    return __inner_data_ptr->feature_mmxext;
}

bool processor_info_provider::get_feature_3dnow() noexcept
{
    return __inner_data_ptr->feature_3dnow;
}

bool processor_info_provider::get_feature_3dnow_ext() noexcept
{
    return __inner_data_ptr->feature_3dnow_ext;
}

bool processor_info_provider::get_feature_sse_4a() noexcept
{
    return __inner_data_ptr->feature_sse_4a;
}

bool processor_info_provider::get_feature_3dnow_prefetch() noexcept
{
    return __inner_data_ptr->feature_3dnow_prefetch;
}

bool processor_info_provider::get_feature_fma_3() noexcept
{
    return __inner_data_ptr->feature_fma_3;
}

bool processor_info_provider::get_feature_fma_4() noexcept
{
    return __inner_data_ptr->feature_fma_4;
}

bool processor_info_provider::get_feature_avx_2() noexcept
{
    return __inner_data_ptr->feature_avx_2;
}

bool processor_info_provider::get_feature_avx_512_f() noexcept
{
    return __inner_data_ptr->feature_avx_512_f;
}

bool processor_info_provider::get_feature_avx_512_dq() noexcept
{
    return __inner_data_ptr->feature_avx_512_dq;
}

bool processor_info_provider::get_feature_avx_512_pf() noexcept
{
    return __inner_data_ptr->feature_avx_512_pf;
}

bool processor_info_provider::get_feature_avx_512_er() noexcept
{
    return __inner_data_ptr->feature_avx_512_er;
}

bool processor_info_provider::get_feature_avx_512_cd() noexcept
{
    return __inner_data_ptr->feature_avx_512_cd;
}

bool processor_info_provider::get_feature_avx_512_bw() noexcept
{
    return __inner_data_ptr->feature_avx_512_bw;
}

bool processor_info_provider::get_feature_avx_512_vl() noexcept
{
    return __inner_data_ptr->feature_avx_512_vl;
}

bool processor_info_provider::get_feature_avx_512_vnni() noexcept
{
    return __inner_data_ptr->feature_avx_512_vnni;
}

bool processor_info_provider::get_feature_avx_512_vbmi() noexcept
{
    return __inner_data_ptr->feature_avx_512_vbmi;
}

bool processor_info_provider::get_feature_avx_512_vbmi_2() noexcept
{
    return __inner_data_ptr->feature_avx_512_vbmi_2;
}

#endif

#pragma endregion
} // namespace callisto::framework