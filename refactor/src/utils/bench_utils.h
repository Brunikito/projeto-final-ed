#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#include <vector>
#include <string>
#include <chrono>

#include "value_utils.h"
#include "less_than.h"
#include "tree_utils.h"

struct GroupedStats {
    long long count = 0;
    double sum = 0.0;
    double sum_sq = 0.0;
    double min;
    double max;

    void add(double stat){
        count++;
        sum += stat;
        sum += stat*stat;
        if (stat < min) min = stat;
        if (stat > max) max = stat;
    }

    double mean() const {
        return (count == 0) ? 0.0 : sum / count;
    }

    double stddev() const {
        if (count < 2) return 0.0;
        return ValueUtils::sqrt((sum_sq - ((sum * sum) / (count - 1))) / (count - 1));
    }
};

struct RotationStats {
    int LL;
    int RR;
    int LR;
    int RL;
};

struct GroupedRotationStats{
    GroupedStats LL;
    GroupedStats RR;
    GroupedStats LR;
    GroupedStats RL;
};

struct MemoryUsage{
    long long numBytes;
    int scaleMultiplier;
    std::string scale;
};

struct ReadDataStats {
    double totalReadTime;
    long long numDocs;
};

struct IndexingStats {
    double totalIndexingTime;
    GroupedStats treeInsertionStats;
    GroupedStats depthStats;
    GroupedStats comparisonStats;
    GroupedStats recoloringStats;
    GroupedRotationStats rotationStats;
    long long totalWordsProcessed;
};

#endif // BENCH_UTILS_H