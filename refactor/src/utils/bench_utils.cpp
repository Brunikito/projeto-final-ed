#include <vector>
#include <string>
#include <chrono>

#include "value_utils.h"
#include "bench_utils.h"

// Adiciona uma amostra para cálculo de estatísticas
void GroupedStats::add(double stat) {
    count++;
    sum += stat;
    sum_sq += stat * stat;
    if (stat < min) min = stat;
    if (stat > max) max = stat;
}

// média aritmética
double GroupedStats::mean() const {
    return (count == 0) ? 0.0 : sum / count;
}

// desvio‑padrão amostral
double GroupedStats::stddev() const {
    if (count < 2) return 0.0;
    return ValueUtils::sqrt((sum_sq - ((sum * sum) / (count - 1))) / (count - 1));
}

// faz merge de estatísticas desta instância com as de outra
void GroupedStats::merge(GroupedStats stats) {
    count += stats.count;  
    sum += stats.sum;      
    sum_sq += stats.sum_sq; 

    if (stats.count > 0) {
        if (count == 0 || stats.min < min) {
            min = stats.min;
        }
    }

    if (stats.count > 0) {
        if (count == 0 || stats.max > max) {
            max = stats.max;
        }
    }
}
