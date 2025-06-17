#include <vector>
#include <string>
#include <chrono>

#include "value_utils.h"
#include "bench_utils.h"

void GroupedStats::add(double stat) {
    count++;
    sum += stat;
    sum_sq += stat * stat;
    if (stat < min) min = stat;
    if (stat > max) max = stat;
}

double GroupedStats::mean() const {
    return (count == 0) ? 0.0 : sum / count;
}

double GroupedStats::stddev() const {
    if (count < 2) return 0.0;
    return ValueUtils::sqrt((sum_sq - ((sum * sum) / (count - 1))) / (count - 1));
}

