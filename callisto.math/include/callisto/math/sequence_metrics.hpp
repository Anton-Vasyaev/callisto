#pragma once

// std
#include <cmath>
#include <vector>
// 3rd party
#include <callisto/framework/exception.hpp>
#include <callisto/framework/types/type_traits.hpp>

namespace c_f = callisto::framework;

namespace callisto::math
{

struct sequence_metrics
{
    template<typename sequence_type>
    static void mean_var(const sequence_type& sequence, double* mean_ptr, double* variance_ptr)
    {
        double mean     = 0.0;
        double variance = 0.0;

        for (auto& value : sequence)
        {
            mean += value;
            variance += std::pow(value, 2);
        }
        mean /= sequence.size();

        variance = std::sqrt(variance / sequence.size() - std::pow(mean, 2));

        if (mean_ptr != nullptr) *mean_ptr = mean;
        if (variance_ptr != nullptr) *variance_ptr = variance;
    }

    template<typename sequence_type_1, typename sequence_type_2>
    static auto normalize_function(const sequence_type_1& f_func, const sequence_type_2& g_func)
    {
        using value_type
            = c_f::senior_conversion_t<sequence_type_1::value_type, sequence_type_2::value_type>;

        std::vector<value_type> g_new;
        g_new.reserve(g_func.size());

        double f_mean, f_var;
        sequence_metrics::mean_var(f_func, &f_mean, &f_var);

        double g_mean, g_var;
        sequence_metrics::mean_var(g_func, &g_mean, &g_var);

        auto alpha = g_var / f_var * f_mean - g_mean;
        auto beta  = f_var / g_var;

        for (size_t i = 0; i < f_func.size(); i++)
        {
            auto new_value = beta * (g_func[i] + alpha);
            g_new.push_back(new_value);
        }

        return g_new;
    }

    template<typename sequence_type_1, typename sequence_type_2>
    static double l1_distance(const sequence_type_1& sequence_1, const sequence_type_2& sequence_2)
    {
        double sum = 0.0;
        for (size_t i = 0; i < sequence_1.size(); i++)
        {
            sum += std::abs(sequence_1[i] - sequence_2[i]);
        }

        return sum / sequence_1.size();
    }

    template<typename sequence_type_1, typename sequence_type_2>
    static double l2_distance(const sequence_type_1& sequence_1, const sequence_type_2& sequence_2)
    {
        double sum = 0.0;
        for (size_t i = 0; i < sequence_1.size(); i++)
        {
            sum += std::pow(sequence_1[i] - sequence_2[i], 2);
        }

        auto distance = std::sqrt(sum) / sequence_1.size();

        return distance;
    }
};

} // namespace callisto::math